#!/usr/bin/perl -w

# NEED ENHANCEMENT
# the utility is not for general purpose currently,
# it is just for learning purpose

use strict;
use diagnostics;
use File::Find;
use File::Copy qw(copy move);
use File::Spec qw(rel2abs);
use 5.014;

my $eslpath =  File::Spec->rel2abs("./ESLPod_Guide");
my $cafepath =  File::Spec->rel2abs("./English_Cafe_Guide");

sub move_file {
    if ( m/ESLPod_\d+_Guide/) {
        move($_, $eslpath);
    }
    elsif ( m/English_Cafe_\d+_Guide/) {
        move($_, $cafepath);
    }
}

say $eslpath;

find(\&move_file, "./Others/");