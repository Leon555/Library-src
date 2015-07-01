#!/usr/bin/perl -w

# Usage:
# perl remove_duplicated_items_winsxs.pl < winsxs_files.txt > older_files.txt

# this utility is used to remove all the duplicated system files in C:\Windows\winsxs
# Rules: the string before sys_ver (6.1.760[0|]) is the file name,
# 1, extract the file name as the CURRENT file name
# 2, move on to extract the next file name, 
#       if this new file name equals the CURRENT file name, records all these names, and then repeat this step
#       else, 
#           if there some dulplicated files, output all the older file names
#           set this file name as the CURRENT file name, then repeact this step
# 3, run the system for some time, if no bad things happen, remove all the older files
# 
# amd64_aspnet_compiler_b03f5f7f11d50a3a_6.1.7600.16385_none_a5a135380060b978
# amd64_aspnet_compiler_b03f5f7f11d50a3a_6.1.7601.18410_none_a5769fe600b79680
# |----------------file name-----------||--ver--| |minor|    |----hash-------|


use diagnostics;
use File::Basename;
use File::Find;
use File::Copy qw(copy move);
use File::Copy::Recursive qw(fcopy rcopy dircopy fmove rmove dirmove pathrmdir);
use 5.014;

my $src = $ARGV[0]; # full file name list
my $dst = $ARGV[1]; # backup file names

my $ver_win7 = "6.1.7600";
my $ver_win7_sp1 = "6.1.7601";
my $VERSION = "6.1.760";

my $full_prev = "";     # previous full file name
my $file_prev = "";     # previous file name
my $minor_prev = "";    # previous minor version to indicate which files be the older

my $full = "";     # current full file name
my $file = "";     # current file name
my $minor = "";    # current minor version to indicate which files be the older

my $winsxs_path = "/cygdrive/c/Windows/winsxs/";
my $winsxs_bak = './winsxs_del/';

$File::Copy::Recursive::CPRFComp = 1;

while (<>) {
    chomp;
    my $full = $_;
    if( m#(?<file>.+)$VERSION[0|1|2]\.(?<minor>\d+)_\w+# ) {
        $file = $+{file};
        $minor = $+{minor};
        
        if($file eq $file_prev && $minor gt $minor_prev) {
            print "$full_prev\n";
            # pathrmdir('./$full_prev') or die $!;
            # dircopy '$full_prev', '$winsxs_bak';#or die $!; !!! NOT SUCCESSFUL
            `mv $full_prev $winsxs_bak`;
        }
        else {
            print "\n";
        }
        $full_prev = $full;
        $file_prev = $file;
        $minor_prev = $minor;
    }
    else {
        print "\n"; # as a marker
        #print $full;
    }
}


dircopy 'amd64_aspnet_regbrowsers_b03f5f7f11d50a3a_6.1.7600.16385_none_96421d40c0e2903e', './winsxs_del/' or die $!;

