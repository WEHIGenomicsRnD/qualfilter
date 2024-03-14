#include <stdio.h>
#include <seqan3/core/debug_stream.hpp>
#include <sharg/all.hpp>

using namespace seqan3;
using namespace std;

int main(int argc, char ** argv)
{
    seqan3::debug_stream << "Hello World!\n";

    string read1;
    string read2;
    string out_prefix;
    string mode = "single";
    int qual = 30;
    int min_len = 30;
    
    sharg::value_list_validator mode_validator{"read1", "read2", "single", "both"};
    sharg::arithmetic_range_validator qual_validator{0, 40};
    sharg::arithmetic_range_validator min_len_validator{0, 1000};
 
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
    parser.add_option(qual,
                      sharg::config{.short_id = 'q',
                      .long_id = "qual",
                      .description = "Quality score to filter on.",
                      .validator = qual_validator});
    parser.add_option(min_len,
                      sharg::config{.short_id = 'n',
                      .long_id = "min-len",
                      .description = "Minimum length of read to keep.",
                      .validator = min_len_validator});
    parser.parse();

    return 0;
}