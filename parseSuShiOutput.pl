#!/usr/bin/perl
# Stefano Lacaprara  <lacaprara@pd.infn.it>  INFN Padova
# 28-Oct-2014
# script to parse the output of SuShi to get a bunch of relevant information
#

# (1) quit unless we have the correct number of command-line args
if ($#ARGV < 0 ) {
    print "\n\tUsage: $0 <SuShi input name*> <verbose>\n";
    print "\n";
    print "\tOuput:\n";
    print "\n\tHiggs-type ggh bbh stability perturbativity unitarity alpha tanbeta mA mH\n";
    print "\n";
    exit;
}
 
my $file = "2HDMC_prodA_ty1_mA300_mH300_tb2p0_sba_SuShi.out";
my $file = $ARGV[0];
my $test=$ARGV[1];

$test && print "Input file: ",$ARGV[0],"\n";

if ( -f $file ) {
  open(INPUT, "< $file") or die "cannot open $file\n";
  while ( <INPUT> ) {
    chomp;
    if ( /1 (.*)  # ggh XS in p/ ) {
      $ggh=$1;
      $test && print "ggh $1\n";
    }
    elsif ( /1 (.*)  # bbh XS in p/ ) {
      $bbh=$1;
      $test && print "bbh $1\n";
    }
    elsif ( /1 *(.*) *# stability/ ) {
      $stab=$1;
      $test && print "stability $1\n";
    }
    elsif ( /2 *(.*) *# perturbativity/ ) {
      $pert=$1;
      $test && print "perturbativity $1\n";
    }
    elsif ( /3 *(.*) *# unitarity/ ) {
      $unit=$1;
      $test && print "unitarity $1\n";
    }
    elsif ( /4 *(.*) *# alpha \(Higgs mixing angle\)/ ) {
      $alpha=$1;
      $test && print "alpha $1\n";
    }
    elsif ( /5 *(.*) *# tan\(beta\)/ ) {
      $tanbeta=$1;
      $test && print "tanbeta $1\n";
    }
    elsif ( /35 *(.*) *# MA in GeV/ ) {
      $mA=$1;
      $test && print "mA $1\n";
    }
    elsif ( /36 *(.*) *# MH in GeV/ ) {
      $mH=$1;
      $test && print "mH $1\n";
    }
    elsif ( /2 *(.*) *# Chosen Higgs particle/) {
      $what=$1;
      $test && print "what $1\n";
    }
  }
  close(INPUT);
} else {
  die "File: $file not found!";
}
#my $part=(($what==1)?"A":($what==2)?"H":"ERROR ");
my $part=(($what==0)?"h":($what==1)?"A":($what==2)?"H":"ERROR ");
my $filename = 'report.txt';
open(my $fh, '>>', $filename) or die "Could not open file '$filename' $!";
print $fh $part,$ggh,$bbh,$stab,$pert,$unit,$alpha,$tanbeta,$mA,$mH,"\n";
close $fh;
print "done\n";

