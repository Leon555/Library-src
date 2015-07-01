#!/usr/bin/perl -w

# NEED ENHANCEMENT

# I use this small program to extract url from a webpage, 
# this can also be replaced by a shell or perl one-liner
# this looks like formal, and can be embeded into other bigger
# programs

use diagnostics;
use File::Basename;
use File::Find;
use File::Copy qw(copy move);
use 5.014;


# my $weburl = ""
my $re = "http:.+?\.mov";

#while ( <> ) {
#	if ( m#(?<url>$re)# ) {
#		say "$+{url}";
#	}
#}

#my $prefix = qw(http://www.mathworks.com/help/pdf_doc/matlab/);
my $prefix = qw(http://www.opensource.apple.com);
$prefix = "";

my %files;
my @urls;
my $line = 1;

while( <> ) {
    # if ( m#href="(?<file>.+\.pdf)".+\>(?<filename>.+)\</a>#m ) {
#         my $file = $+{file};
#         $file =~ s/^\.\.\///;
#         push @urls, $prefix . $file;
#         $file =~ s/otherdocs\///;
#         $files{$file} = $+{filename};
#         say $file;
#     }
#     elsif ( m#href="(?<file>.+)\/index.+\>(?<filename>.+)\</a>#m ) {
#         push @urls, $prefix . $+{file} . "\/" . $+{file} . ".pdf";
#         push @urls, $prefix . $+{file} . "\/" . $+{file} . "_tb.pdf";
#         push @urls, $prefix . $+{file} . "\/" . $+{file} . "_ref.pdf";
#         $files{$+{file} . ".pdf"} = $+{filename} . " User\'s Guide";
#         $files{$+{file} . "_tb.pdf"} = $+{filename} . " User\'s Guide";
#         $files{$+{file} . "_ref.pdf"} = $+{filename} . " Reference";
#         #say $+{file};
#     }
	
	if( m#href=\'(?<file>http.*?\.(gz|bz2))\'# ) {
        my $url = $+{file};
        $url =~ s/http.+'//;
		say $prefix . $url;
 	}
	#if( m#(?<char>..)\k<char># ) {
	#	say $line . ":" . $+{char};
	#}
	$line++;
}

for my $url (@urls) {
    say "$url";
}

foreach my $fn (sort keys %files) {
    say "$fn -> $files{$fn}";
}

sub change_name {
	chomp;
	my $orig = $_;

	my ($name, $folder, $ext) ;
	my $new;
    
    say $_;

	if( -f ) {
		($name, $folder, $ext)  = fileparse("$orig", qr/\.[^.]+/);
        # remove the trailing characters after comma (,)
        #$name =~ s/,.*//;
		# replace white space or dot (.) into underscore _
        #$new = join('_', split(/ |\./, $name)) . "$ext";
        $new = $files{$name . $ext} . $ext;
	}
	elsif( -d ) {
		$new = join('_', split(/ |\./, $orig));
	}

	if( $orig ne $new ) {
		say "$orig, $new";
		move($orig, $new);
	}
}

#find(\&change_name, "/Volumes/Backup/Temp/full");
