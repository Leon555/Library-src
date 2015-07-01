#!/usr/bin/perl -w

# this utility is used to unify all the file names
# here are rules:
# 1, separate words with underline '_'
# 2, separate title and subtitle with dash '-'

# BUG: the folder name has been changed before the items in them
# we can't stick to function find, and then I can traverse the whole
# file system by myself

# Temporaray solution: run the script a few more times

use diagnostics;
use File::Basename;
use File::Find;
use File::Copy qw(copy move);
use 5.014;

my $dest = $ARGV[0];

sub change_name {
	chomp;
	my $orig = $_;

	my ($name, $folder, $ext) ;
	my $new;

	if( -f ) {
		($name, $folder, $ext)  = fileparse("$orig", qr/\.[^.]+/);
        # remove the trailing characters after comma (,)
        $name =~ s/,.*//;
		# replace white space or dot (.) into underscore _
        $new = join('_', split(/ |\./, $name)) . "$ext";
	}
	elsif( -d ) {
		$new = join('_', split(/ |\./, $orig));
	}

	if( $orig ne $new ) {
		say "$orig, $new";
		move($orig, $new);
	}
}

find(\&change_name, "$dest");

