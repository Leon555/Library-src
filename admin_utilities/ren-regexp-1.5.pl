#!/usr/bin/perl
## $Id: ren-regexp,v 1.5 2003/03/09 04:28:12 forman Exp forman $ 
##
## Author:        Michael Forman <Michael.Forman@Colorado.EDU>
## Creation Date:  Date: 2000/07/31 02:47:42 GMT
## Last Revision: $Date: 2003/03/09 04:28:12 $ 
## Revision:      $Revision: 1.5 $
##
## Copyright (C) 1999, 2000 Michael Forman.  All rights reserved.
## This program is free software; you can redistribute it
## and/or modify it under the same terms as Perl itself.
## Please see the Perl Artistic License.
#

use Getopt::Long;
use File::Copy;

#---------------------------------------------------------------------------
GetOptions(
  "h|help"		=> \$help,
  "d|debug" 		=> \$debug,
  "t|test" 		=> \$test,
  "v|version" 		=> \$vers,
  #---------------------------------
  "c|color"		=> \$color,
  "u|underline"		=> \$under,
  "g|global"		=> \$global,
  "i|insensitive"	=> \$insen,
  "f|force"		=> \$force,
  "q|quiet" 		=> \$quiet,
);
#---------------------------------------------------------------------------
if($help){ exec("perldoc $0"); }
if($vers){ version(); }
if($#ARGV == -1){ usage(); }
#---------------------------------------------------------------------------
## I turned on color and underlining by default.
## You can comment these out or override them
## using "--nocolor" and "--nounderline".
#
if($color eq ""){ $color = 1; }
if($under eq ""){ $under = 1; }
#---------------------------------------------------------------------------

if($under && $color){
  $CG = ansi_color("g","u");
  $CR = ansi_color("r","u");
  $CO = ansi_color("y","u");
  $CL = ansi_color("d","n");
}elsif($under){
  $CG = ansi_color("d","u");
  $CR = ansi_color("d","u");
  $CO = ansi_color("d","u");
  $CL = ansi_color("d","n");
}elsif($color){
  $CG = ansi_color("g","n");
  $CR = ansi_color("r","n");
  $CO = ansi_color("y","n");
  $CL = ansi_color("d","n");
}

##
## Store regular expressions
#
foreach $re (@ARGV){
  ## Take the following forms:
  ##   s/a/b/[ig]
  ##    /a/b/[ig]
  ##     a/b/[ig]
  ##     a/b
  #
  if(-e $re){ last; }		# if file, end of regexps
  chomp($re);

  $re =~ s/^\w*s?\///;
  ($pa,$tx,$md) = split(/\//,$re); 
  push(@re,$re);

  if($global && (!($md =~ /g/))){ $md.= "g"; }
  if($insen  && (!($md =~ /i/))){ $md.= "i"; }

  $pa{$re} = $pa;	# regexp
  $tx{$re} = $tx;	# replacement
  $md{$re} = $md;	# modifier
  $dl{$re} = $dl; 	# delimiter
}

if($#re == -1){ usage(); }

$nsp = int(($#re+1)/10)+2;
$spc = " " x $nsp;

foreach $re (@re){
  shift(@ARGV);
}


##
## Apply substitutions
#
while($ofile = shift(@ARGV)){
  $nfile = $ofile;
  $pfile = $ofile;
  $nre = 0;
  foreach $re (@re){
    $pa = $pa{$re};
    $tx = $tx{$re};
    $md = $md{$re};
    $dl = $dl{$re};

    eval("\$nfile =~ s/$pa/$tx/$md");
    if($pfile ne $nfile){ 
      if($ofile[$#ofile] ne $ofile){ push(@ofile, $ofile); }
      ##
      ## A regexp worked!
      ## Store begining end and regexp
      #
      $pf{$ofile,$re} = $pfile;
      $nf{$ofile,$re} = $nfile;
      $rn{$ofile,$re} = $nre;
      $re{$ofile}    .= "$re"." __rEgExP__ ";
      $pfile = $nfile;
    }
    $nre++;
  }
  $nf{$ofile} = $nfile;
}


##
## Output and move
#
foreach $ofile (@ofile){
  ##
  ## Output
  #
  $prc = "";
  @re = split(/ __rEgExP__ /,$re{$ofile});

  print("\n");

  for($i=0;$i<=$#re;$i++){
    $re = @re[$i];
    if(!$quiet){
      $pa = $pa{$re};		# pattern
      $tx = $tx{$re};		# trans
      $md = $md{$re};		# mod

      $pp = $pa{$re[$i+1]};	# trans
      $m2 = $md{$re[$i+1]};	# trans

      $of = $ofile;		# old file name
      $pf = $pf{$ofile,$re};	# new file name
      $nf = $nf{$ofile,$re};	# new file name
      $rn = $rn{$ofile,$re};	# regexp number

      if($color||$under){ 
        ($pf, $nf) = color_regexp3($pf, $pa, $tx, $md, $nf, $pp, "", $m2);
      }

      $prn = $rn + 1;
      if($nsp > 2){ $prn =~ s/^(\d)$/0$1/; $spc = "   "; }
      if($i==0){ print("$spc$pf\n"); }
      print("$prn $nf\n"); 
    }
  }
  ##
  ## Move
  #
  $nfile = $nf{$ofile};
  if(!$test){ 
    if((!-e $nfile)||($force)){ move("$ofile","$nfile"); }
    else{ print(STDERR "Cannot move \"$nfile\": file exists.\n"); }
  }else{
    #print("mv \"$ofile\" \"$nfile\"\n"); 
  }
}

if(!$quiet){
  print("\n");
}


#---------------------------------------------------------------------------
 sub color_regexp3{ my($p1, $r1, $t1, $m1, $p2, $r2, $t2, $m2) = @_;
  ##
  ## Uses three colors to highlight changes in names.
  #
  my($c1, $c2, $c3);
  my(@c3, @r1);
  my($str,$pr);
  my($i);

  $c1 = restcol($p1,$r1,  $t1,$m1,1);
  $c2 = restcol($p2,$r2,"\$1",$m2,2);
  $c3 = stradd($c1, $c2);

  eval("\$p1 =~ s/($r1)/$CR\$1$CL/$m1;"); 

  if($debug){
    print("  $c1  s/$r1/$t1/$m1\n");
    print(" +$c2  /$r2/$m2\n");
    print(" =$c3  sum\n");
  }

  @c3 = split(//, $c3);
  @p2 = split(//, $p2);

  for($i=0;$i<=$#c3;$i++){
    if($c3[$i] != $pr){
      if($c3[$i] == 0){
        $str.= "$CL$p2[$i]";
      }elsif($c3[$i] == 1){
        $str.= "$CL$CG$p2[$i]";
      }elsif($c3[$i] == 2){
        $str.= "$CL$CR$p2[$i]";
      }elsif($c3[$i] == 3){
        $str.= "$CL$CO$p2[$i]";
      }
    }else{
      $str.= "$p2[$i]";
    }
    $pr = $c3[$i];
  }
  $p2 = $str."$CL";

  return($p1,$p2);
}
#---------------------------------------------------------------------------
sub restcol { my($st,$re,$tx,$md,$k) = @_;
  my(@st);
  my($i,$n,$col);

  eval("\$st =~ s/($re)/ __ReGeXp__ $tx __ReGeXp__ /$md;");

  @st = split(/ __ReGeXp__ /,$st);

  for($i=0;$i<=$#st;$i++){
    $n = $i%2*$k;
    $col.= $n x length($st[$i]);
  }

  return($col);
}
#---------------------------------------------------------------------------
sub stradd { my($a, $b) = @_;
  my(@a,@b,@c);
  my($i,$c);
  my($sa) = 1;
  my($sb) = 1;

  if($a =~ s/^-//){ $sa*= -1; }
  if($b =~ s/^-//){ $sb*= -1; }

  @a = split(//,$a);
  @b = split(//,$b);

  for($i=0;$i<=$#a;$i++){
    $c[$i] = $sa * $a[$i] + $sb * $b[$i];
    if($c[$i] < 0){ $c[$i] = 0; }
  }
  $c = join('', @c);

  return($c);
}
#---------------------------------------------------------------------------
sub ansi_color { my($color,$attrb) = @_;
  my($ansi);
  ##
  ## Colors
  ##
  ## Attribute codes:
  ## 00=none 01=bold 04=underscore 05=blink 07=reverse 08=concealed
  ##
  ## Text color codes:
  ## 30=black 31=red 32=green 33=yellow 34=blue 35=magenta 36=cyan 37=white
  ##
  ## Background color codes:
  ## 40=black 41=red 42=green 43=yellow 44=blue 45=magenta 46=cyan 47=white
  #
  $ansi = "\e[";

     if($color =~ /d(efault)?/i){   $ansi.= "00";  }
  elsif($color =~ /r(ed)?/i){       $ansi.= "31";  }
  elsif($color =~ /g(reen)?/i){     $ansi.= "32";  }
  elsif($color =~ /y(ellow)?/i){    $ansi.= "33";  }
  elsif($color =~ /b(lue)?/i){      $ansi.= "34";  }
  elsif($color =~ /m(agenta)?/i){   $ansi.= "35";  }
  elsif($color =~ /c(yan)?/i){      $ansi.= "36";  }
  elsif($color =~ /w(hite)?/i){     $ansi.= "37";  }

     if($attrb =~ /n(ormal)?/i){    $ansi.= ";00"; }
  elsif($attrb =~ /b(old)?/i){      $ansi.= ";01"; }
  elsif($attrb =~ /u(nderline)?/i){ $ansi.= ";04"; }

  $ansi.= "m";

  return($ansi);
}
#---------------------------------------------------------------------------
sub usage {
  print("\n");
  print("usage: ren-regexp [regexp ...] [file ...]\n");
  print("\n");
  exit;
}

#---------------------------------------------------------------------------
sub version {
  my($date) = "\$Date: 2003/03/09 04:28:12 $_";
  my($rvsn) = "\$Revision: 1.5 $_";
  my($rcsd) = "\$Id: ren-regexp,v 1.5 2003/03/09 04:28:12 forman Exp forman $_";

  $date =~ s/(.*: +)(.*?)(\s*$)/$2/g;
  $rvsn =~ s/(.*: +)(.*?)(\s*$)/$2/g;
  $rcsd =~ s/(.*: +)(.*?)(\s*$)/$2/g;

  print <<EOF;

Program:       ren-regexp v$rvsn

Author:        Michael Forman <Michael.Forman\@Colorado.EDU>
Creation Date: 2000/07/31 02:47:42 GMT
Last Revision: $date GMT
Revision:      $rcsd

Copyright (C) 2002, 2003 Michael Forman.  All rights reserved.
This program is free software; you can redistribute it
and/or modify it under the same terms as Perl itself.

EOF
  exit;
}
#---------------------------------------------------------------------------
##
## Use "perldoc ren-regexp" to read the man page below.
#
__END__

=head1 NAME

B<ren-regexp> - Rename files by the application of regular expressions

=head1 SYNOPSIS 

B<ren-regexp> 
S<[ B<-dhtv> ]> 
S<[ B<-cfgiqu> ]> 
S<[I<regexp ...>]> 
S<[I<file ...>]>


=head1 DESCRIPTION

B<ren-regexp> applies one or more regular expressions 
to a list of file names.
This provides a method of applying common modifications
to many files that would otherwise require repetitive,
atomic file operations.


=head1 OPTIONS

B<-c --color>

B<-u --underline>

The "B<--color>" and "B<--underline>" options can be used
together or separately to highlight changes in the filename
as the regular expression are applied.

B<-d --debug>

Print additional information useful for debugging.

B<-f --force>

If the new file exists, this will force an overwrite.

B<-g --global>

Apply all regular expressions globally to a filename.
This is equivalent to appending a "I<g>" to the end of each
regular expression as in "I<s/regexp/string/B<g>>".

B<-h --help>

Prints this information.

B<-i --insensitive>

Apply all regular epxression without sensitivity to case.
This is equivalent to appending an "I<i>" to the end of each
regular expression as in "I<s/regexp/string/B<i>>".

B<-q --quiet>

B<ren-regexp> is rather verbose for a unix program.
Consider this a feature to prevent data loss.
To keep things quiet, use this option.

B<-t --test>

Test the application of the regular expressions without renaming the files.
This is highly recommended to prevent the loss of data.


=head1 EXAMPLE

The following example shows standard usage.
The regular expression, "I<s/.mp3/ of 3.mp3/>", is applied to
the three files resulting in files matching the pattern
"I<PI-01 of 3.mp3>".

B<ren-regexp> B<"s/.mp3/ of 3.mp3/"> B<PI-01.mp3 PI-02.mp3 PI-03.mp3>


The following examples all have the same result.
Note that the initial "I<s/>" are both optional
with the final "I</>" option if there is no modifier.

B<ren-regexp> B<"s/A/B/i"> B<*>

B<ren-regexp> B<-i> B<"s/A/B/"> B<*>

B<ren-regexp> B<"A/B/i"> B<*>

B<ren-regexp> B<-i> B<"A/B"> B<*>

The following example shows three regular expressions
applied in turn on a filename.  
The file progresses from the original of "I<ABCD.txt>"
to "I<abCD.txt>", "I<ABcD.txt>", and finally "I<AcDB.txt>".
The single quote is necessary to prevent the shell from
expanding the regular expression variables, "I<$1>" and "I<$2>".

B<ren-regexp> B<"AB/ab"> B<"abC/ABc"> B<'(B)(cD)/$2$1'> ABCD.txt 

=head1 BUGS

The color ouput doesn't like regular expressions variables (i.e., "I<$1>").

=head1 SEE ALSO

mv    

=head1 AUTHOR AND COPYRIGHT

Michael Forman <Michael.Forman@Colorado.EDU>

Copyright (C) 2000, 2001, 2002 Michael Forman.  All rights reserved.
This program is free software; you can redistribute it
and/or modify it under the same terms as Perl itself.
Please see the Perl Artistic License.

=head1 VERSION

Current Revision:  $Revision: 1.5 $
Last Modification: $Date: 2003/03/09 04:28:12 $

=pod SCRIPT CATEGORIES
UNIX/System_administration

=pod OSNAMES
Any

