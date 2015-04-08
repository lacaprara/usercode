#!/usr/bin/perl
# Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
# 28-Oct-2014
# script to parse the output of 2HDMC to get a bunch of relevant information
#
use warnings;

# (1) quit unless we have the correct number of command-line args
if ($#ARGV < 0 ) {
    print "\n\tUsage: $0 <2HDMC input name*> <verbose>\n";
    print "\n";
    print "\tOuput:\n";
    print "\n\tHiggs-type ggh bbh stability perturbativity unitarity alpha tanbeta mA mH\n";
    print "\n";
    exit;
}

#my $file = "2HDMC_prodH_ty1_mA300_mH300_tb2p0_sba_2HDMC.out";
my $file = $ARGV[0];
my $test=$ARGV[1];

my $h2ss=$h2cc=$h2bb=$h2ee=$h2mumu=$h2tautau=$h2gamgam=$h2ZZ=$h2WW=$h2Zgam=$h2gluglu="0.0 ";
my $H2ss=$H2cc=$H2bb=$H2tt=$H2ee=$H2mumu=$H2tautau=$H2gamgam=$H2ZZ=$H2WW=$H2Zgam=$H2gluglu=$H2hh=$H2AA=$H2HCHC=$H2ZA=$H2WHC=$H2HCW="0.0 ";
my $A2ss=$A2cc=$A2bb=$A2tt=$A2ee=$A2mumu=$A2tautau=$A2gamgam=$A2Zgam=$A2gluglu=$A2Zh="0.0 ";
my $HC2us=$HC2ub=$HC2cd=$HC2cs=$HC2cb=$HC2td=$HC2ts=$HC2tb=$HC2enue=$HC2munumu=$HC2taunutau=$HC2Wh="0.0 ";

if ( -f $file ) {
  open(INPUT, "< $file") or die "cannot open $file\n";
  while ( <INPUT> ) {
    chomp;
    if ( /1 *(.*) *#  Valid parameters/ ) {
      $valid=$1;
      $test && print "Valid parameters $1\n";
    }
    elsif ( /2 *(.*) *#  Tree-level unitarity/ ) {
      $unit=$1;
      $test && print "unitarity $1\n";
    }
    elsif ( /3 *(.*) *#  Perturbativity/ ) {
      $pert=$1;
      $test && print "Perturbativity $1\n";
    }
    elsif ( /4 *(.*) *#  Stability/ ) {
      $stab=$1;
      $test && print "Stability $1\n";
    }
    elsif ( /37 *(.*) *# Mhc/ ) {
      $mhc=$1;
      $test && print "Mhc $1\n";
    }
    elsif ( /3 *(.*) *# tan\(beta\)/ ) {
      $tanbeta=$1;
      $test && print "tanbeta $1\n";
    }
    elsif ( /20 *(.*) *# sin\(beta-alpha\)/ ) {
      $sba=$1;
      $test && print "sin(beta-alpha) $1\n";
    }
    elsif ( /21 *(.*) *# cos\(beta-alpha\)/ ) {
      $cba=$1;
      $test && print "cos(beta-alpha) $1\n";
    }
    elsif ( /18 *(.*) *# m_12\^2/ ) {
      $m12=$1;
      $test && print "m12^2 $1\n";
    }
    if ( /^Block ALPHA/ .. /^Block UCOUPL/ ) {
      if ( /(.*)  # alpha/) {
        $alpha=$1;
        $test && print "alpha $1\n";
      }
    }
# h BR
    if ( /^DECAY  25/ .. /^DECAY  35/ ) {
      if ( /^DECAY  25 (.*)  # h1/) {
        $gammah=$1;
        $test && print "gammah $1\n";
      }
      elsif ( /(.*) *2       3    -3/) { $h2ss=$1; }
      elsif ( /(.*) *2       4    -4/) { $h2cc=$1; }
      elsif ( /(.*) *2       5    -5/) { $h2bb=$1; }
      elsif ( /(.*) *2      11   -11/) { $h2ee=$1; }
      elsif ( /(.*) *2      13   -13/) { $h2mumu=$1; }
      elsif ( /(.*) *2      15   -15/) { $h2tautau=$1; }
      elsif ( /(.*) *2      22    22/) { $h2gamgam=$1; }
      elsif ( /(.*) *2      23    23/) { $h2ZZ=$1; }
      elsif ( /(.*) *2      24   -24/) { $h2WW=$1; }
      elsif ( /(.*) *2      23    22/) { $h2Zgam=$1; }
      elsif ( /(.*) *2      21    21/) { $h2gluglu=$1; }
    }
# H BR
    if ( /^DECAY  35 *(.*)   # h2/ .. /^DECAY  36/ ) {
      if ( /^DECAY  35 *(.*)  # h2/) {
        $gammaH=$1;
        $test && print "gammaH $1\n";
      }
      elsif ( /(.*) *2       3    -3/) { $H2ss=$1; }
      elsif ( /(.*) *2       4    -4/) { $H2cc=$1; }
      elsif ( /(.*) *2       5    -5/) { $H2bb=$1; }
      elsif ( /(.*) *2       6    -6/) { $H2tt=$1; }
      elsif ( /(.*) *2      11   -11/) { $H2ee=$1; }
      elsif ( /(.*) *2      13   -13/) { $H2mumu=$1; }
      elsif ( /(.*) *2      15   -15/) { $H2tautau=$1; }
      elsif ( /(.*) *2      22    22/) { $H2gamgam=$1; }
      elsif ( /(.*) *2      23    23/) { $H2ZZ=$1; }
      elsif ( /(.*) *2      24   -24/) { $H2WW=$1; }
      elsif ( /(.*) *2      23    22/) { $H2Zgam=$1; }
      elsif ( /(.*) *2      21    21/) { $H2gluglu=$1; }
      elsif ( /(.*) *2      25    25/) { $H2hh=$1; }
      elsif ( /(.*) *2      36    36/) { $H2AA=$1; }
      elsif ( /(.*) *2      37   -37/) { $H2HCHC=$1; }
      elsif ( /(.*) *2      23    36/) { $H2ZA=$1; }
      elsif ( /(.*) *2      24   -37/) { $H2WHC=$1; }
      elsif ( /(.*) *2      37   -24/) { $H2HCW=$1; }
    }
# A BR
    if ( /^DECAY  36/ .. /^DECAY  37/ ) {
      if ( /^DECAY  36 *(.*)  # h3/) {
        $gammaA=$1;
        $test && print "gammaA $1\n";
      }
      elsif ( /(.*) *2       3    -3/) { $A2ss=$1; }
      elsif ( /(.*) *2       4    -4/) { $A2cc=$1; }
      elsif ( /(.*) *2       5    -5/) { $A2bb=$1; }
      elsif ( /(.*) *2       6    -6/) { $A2tt=$1; }
      elsif ( /(.*) *2      11   -11/) { $A2ee=$1; }
      elsif ( /(.*) *2      13   -13/) { $A2mumu=$1; }
      elsif ( /(.*) *2      15   -15/) { $A2tautau=$1; }
      elsif ( /(.*) *2      22    22/) { $A2gamgam=$1; }
      elsif ( /(.*) *2      23    22/) { $A2Zgam=$1; }
      elsif ( /(.*) *2      21    21/) { $A2gluglu=$1; }
      elsif ( /(.*) *2      23    25/) { $A2Zh=$1; }
    }
# H+ BR
    if ( /^DECAY  37/ .. /^BLOCK MGUSER/ ) {
      if ( /^DECAY  37 *(.*)  # /) {
        $gammaHC=$1;
        $test && print "gammaHC $1\n";
      }
      elsif ( /(.*) *2       2    -3/) { $HC2us=$1; }
      elsif ( /(.*) *2       2    -5/) { $HC2ub=$1; }
      elsif ( /(.*) *2       4    -1/) { $HC2cd=$1; }
      elsif ( /(.*) *2       4    -3/) { $HC2cs=$1; }
      elsif ( /(.*) *2       4    -5/) { $HC2cb=$1; }
      elsif ( /(.*) *2       6    -1/) { $HC2td=$1; }
      elsif ( /(.*) *2       6    -3/) { $HC2ts=$1; }
      elsif ( /(.*) *2       6    -5/) { $HC2tb=$1; }
      elsif ( /(.*) *2     -11    12/) { $HC2enue=$1; }
      elsif ( /(.*) *2     -13    14/) { $HC2munumu=$1; }
      elsif ( /(.*) *2     -15    16/) { $HC2taunutau=$1; }
      elsif ( /(.*) *2      24    25/) { $HC2Wh=$1; }
    }
  }
  close(INPUT);
} else {
  die "File: $file not found!";
}

my $filename = 'report.txt';
open(my $fh, '>>', $filename) or die "Could not open file '$filename' $!";
print $fh "2HDMC ",$valid,$unit,$pert,$stab,$mhc,$tanbeta,$sba,$cba,$m12,$gammah,$gammaH,$gammaA,$gammaHC,"\n";
print $fh "BRh ",$h2ss, $h2cc, $h2bb, $h2ee, $h2mumu, $h2tautau, $h2gamgam, $h2ZZ, $h2WW, $h2Zgam, $h2gluglu,"\n";
print $fh "BRH ",$H2ss, $H2cc, $H2bb, $H2tt, $H2ee, $H2mumu, $H2tautau, $H2gamgam, $H2ZZ, $H2WW, $H2Zgam, $H2gluglu, $H2hh, $H2AA, $H2HCHC, $H2ZA, $H2WHC, $H2HCW, "\n";
print $fh "BRA ",$A2ss, $A2cc, $A2bb, $A2tt, $A2ee, $A2mumu, $A2tautau, $A2gamgam, $A2Zgam, $A2gluglu, $A2Zh,"\n";
print $fh "BRHC ",$HC2us, $HC2ub, $HC2cd, $HC2cs, $HC2cb, $HC2td, $HC2ts, $HC2tb, $HC2enue, $HC2munumu, $HC2taunutau, $HC2Wh,"\n";
close $fh;
print "done\n";
