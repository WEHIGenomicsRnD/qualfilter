#include <stdio.h>
#include <seqan3/core/debug_stream.hpp>
#include <seqan3/io/sequence_file/all.hpp>
#include <seqan3/utility/views/zip.hpp>
#include <sharg/all.hpp>

using namespace seqan3;
using namespace seqan3::literals;
using namespace std;

bool read_passes_filter(std::vector<seqan3::phred42> quals, int min_qual, float min_pass_percent) {
    int read_len = 0;
    int bases_passed = 0;
    float pass_percent = 0;

    for (auto && q : quals) {
        ++read_len;
        if (static_cast<int>(q.to_phred()) >= min_qual) {
            ++bases_passed;
        }
    }
    if (read_len == 0) {
        return false;
    } else {
        pass_percent = (static_cast<float>(bases_passed) / static_cast<float>(read_len)) * 100;
        if (pass_percent >= min_pass_percent) {
            return true;
        }
    }
    return false;
}

int main(int argc, char ** argv)
{
    string read1;
    string read2;
    string out_prefix;
    string mode = "single";
    int min_qual = 30;
    float min_pass_percent = 80;
    
    sharg::value_list_validator mode_validator{"read1", "read2", "single", "both"};
    sharg::arithmetic_range_validator qual_validator{0, 40};
    sharg::arithmetic_range_validator min_pass_percent_validator{0, 100};
 
    sharg::parser parser{"qualfilter", argc, argv};
    parser.add_subsection("Input/output options:");
    parser.add_option(read1,
                      sharg::config{.short_id = 'l',
                      .long_id = "read1",
                      .description = "Read 1 FASTQ file.",
                      .required = true,
                      .validator = sharg::input_file_validator{{"fq.gz", "fastq.gz", "fq", "fastq"}}});
    parser.add_option(read2,
                      sharg::config{.short_id = 'r',
                      .long_id = "read2",
                      .description = "Read 2 FASTQ file.",
                      .required = true,
                      .validator = sharg::input_file_validator{{"fq.gz", "fastq.gz", "fq", "fastq"}}});
    parser.add_option(out_prefix,
                      sharg::config{.short_id = 'o',
                      .long_id = "out-prefix",
                      .description = "Prefix for output files.",
                      .required = true});
    parser.add_option(mode,
                      sharg::config{.short_id = 'm',
                      .long_id = "mode",
                      .description = "Mode to run in.",
                      .validator = mode_validator});               
    parser.add_option(min_qual,
                      sharg::config{.short_id = 'q',
                      .long_id = "min-qual",
                      .description = "Quality score to filter on.",
                      .validator = qual_validator});
    parser.add_option(min_pass_percent,
                      sharg::config{.short_id = 'p',
                      .long_id = "min-pass-percent",
                      .description = "Minimum percent (0-100) of bases that must pass the quality filter.",
                      .validator = min_pass_percent_validator});
    parser.parse();

    // tracking variables
    int passed_reads = 0;
    int failed_reads = 0;

    seqan3::sequence_file_input fin1{read1};
    seqan3::sequence_file_input fin2{read2};
 
    seqan3::sequence_file_output fout{out_prefix + "_R1.fq"};
    seqan3::sequence_file_output fout2{out_prefix + "_R2.fq"};

    bool pass1 = false;
    bool pass2 = false;

    for (auto && [rec1, rec2] : seqan3::views::zip(fin1, fin2)) {
        if (rec1.base_qualities().size() != rec1.sequence().size() || rec2.base_qualities().size() != rec2.sequence().size()) {
            throw std::runtime_error("Sequence and quality scores are not the same length.");
        }
        
        if (mode == "read1") {
            pass1 = read_passes_filter(rec1.base_qualities(), min_qual, min_pass_percent);
        } else if (mode == "read2") {
            pass2 = read_passes_filter(rec2.base_qualities(), min_qual, min_pass_percent);
        } else {
            pass1 = read_passes_filter(rec1.base_qualities(), min_qual, min_pass_percent);
            pass2 = read_passes_filter(rec2.base_qualities(), min_qual, min_pass_percent);
        }

        if (mode == "read1" && pass1) {
            ++passed_reads;
            fout.push_back(rec1); fout2.push_back(rec2);
        } else if (mode == "read2" && pass2) {
            ++passed_reads;
            fout.push_back(rec1); fout2.push_back(rec2);
        } else if (mode == "single" && (pass1 || pass2)) {
            ++passed_reads;
            fout.push_back(rec1); fout2.push_back(rec2);
        } else if (mode == "both" && pass1 && pass2) {
            ++passed_reads;
            fout.push_back(rec1); fout2.push_back(rec2);
        } else {
            ++failed_reads;
        }
    }

    cout << "Passed reads: " << passed_reads << endl;
    cout << "Failed reads: " << failed_reads << endl;
    cout << "Total reads: " << passed_reads + failed_reads << endl;

    return 0;
}
