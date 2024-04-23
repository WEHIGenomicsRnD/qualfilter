#!/bin/sh

./build/qualfilter \
    -l test_data/sample_R1.fastq.gz \
    -r test_data/sample_R2.fastq.gz \
    -o test \
    -m both \
    -q 10 \
    -n 20
