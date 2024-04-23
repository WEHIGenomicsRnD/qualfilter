# QualFilter 

Perform quality filtering on paired reads when read1, read2, a single read, or both reads pass the quality filter. Always keeps the paired reads together.

This is a C++ implementation of the [read_qual_filter.py script](https://github.com/WEHIGenomicsRnD/genomics-toolkit/blob/5e91668f5c9b3fd1f25e07339b9cb40ce859ecb6/bin/read_qual_filter.py) for performance reasons.

## Installation

First clone the repository:

```bash
git clone https://github.com/WEHIGenomicsRnD/qualfilter.git
```

Now you have to install the dependencies [shargs](https://docs.seqan.de/sharg/main_user/index.html) and [seqan3](https://docs.seqan.de/seqan3/main_user/index.html):

```bash
git clone --recurse-submodules https://github.com/seqan/sharg-parser.git
git clone --recurse-submodules https://github.com/seqan/seqan3.git
```

Now build the project:

```bash
./build.sh
```

You can now run the test:

```bash
./test.sh
```

## Usage

The test.sh shows example usage:

```bash
./build/qualfilter \
    -l test_data/sample_R1.fastq.gz \
    -r test_data/sample_R2.fastq.gz \
    -o test \
    -m both \
    -q 10 \
    -n 20
```

```
OPTIONS

  Input/output options:
    -l, --read1 (std::string)
          Read 1 FASTQ file.. The input file must exist and read permissions must be granted. Valid file extensions
          are: [fq.gz, fastq.gz, fq, fastq].
    -r, --read2 (std::string)
          Read 2 FASTQ file.. The input file must exist and read permissions must be granted. Valid file extensions
          are: [fq.gz, fastq.gz, fq, fastq].
    -o, --out-prefix (std::string)
          Prefix for output files.
    -m, --mode (std::string)
          Mode to run in. Default: "single". Value must be one of [read1, read2, single, both].
    -q, --min-qual (signed 32 bit integer)
          Quality score to filter on. Default: 30. Value must be in range [0,40].
    -n, --min-len (signed 32 bit integer)
          Minimum length of read to keep. Default: 30. Value must be in range [0,1000].

  Common options
    -h, --help
          Prints the help page.
    -hh, --advanced-help
          Prints the help page including advanced options.
    --version
          Prints the version information.
    --copyright
          Prints the copyright/license information.
    --export-help (std::string)
          Export the help page information. Value must be one of [html, man, ctd, cwl].
    --version-check (bool)
          Whether to check for the newest app version. Default: true
```
