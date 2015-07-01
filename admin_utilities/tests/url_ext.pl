#!/usr/bin/perl -w

# NEED ENHANCEMENT

# I use this small program to extract url from a webpage, 
# this can also be replaced by a shell or perl one-liner
# this looks like formal, and can be embeded into other bigger
# programs

use diagnostics;
use 5.014;


# my $weburl = ""
my $re = "http:.+?\.mov";

while ( <> ) {
	if ( m#(?<url>$re)# ) {
		say "$+{url}";
	}
}
