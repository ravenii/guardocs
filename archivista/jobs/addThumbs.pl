#!/usr/bin/perl

=head1 addImages.pl -> add images to archivista db from output folders

  (c) v1.0 - 30.12.2005 by Archivista GmbH, Urs Pfister

=cut

use lib qw(/home/cvs/archivista/jobs);
use strict;
use DBI;
use AVJobs;

my @dbs = ("avgmbh"); # databases we need to add images
my $begnr = 1; # first doc.
my $endnr = 13000; # last doc.
my $dbh;

if ($dbh=MySQLOpen()) {
  # coonection is ok
  foreach (@dbs) {
	  my $db1 = $_;
    my $jpegqual=getBoxParameterRead($dbh,$db1,"JpegQuality",10,100,33);
    my $fact=getBoxParameterRead($dbh,$db1,"PrevScaling",0,100,20);
    $fact=10 if $fact<10 && $fact !=0;
    my $fact1 = $fact/100;
	  my $aktnr = $begnr;
		while($aktnr<=$endnr) {
		  my $sql = "select Seiten,ArchivArt from $db1.archiv " .
			          "where Laufnummer=$aktnr";
			my ($seiten,$art) = $dbh->selectrow_array($sql);
			logit("add thumbs in $db1: $aktnr-$seiten");
			for (my $c=1;$c<=$seiten;$c++) {
			  my $nr = ($aktnr*1000)+$c;
				my $sql = "select BildInput from $db1.archivbilder " .
				           "where Seite=$nr";
				my @row = $dbh->selectrow_array($sql); 
				if ($row[0] ne "") {
          my $img = ExactImage::newImage();
          ExactImage::decodeImage($img,$row[0]);
					my $bit = ExactImage::imageColorspace($img);
				  my $depth=1;
					$depth=3 if $bit ne "gray1";
					my $image1;
          if ($depth==1) {
            ExactImage::imageBilinearScale($img,$fact1);
            $image1 = ExactImage::encodeImage($img,"tiff");
          } else {
            ExactImage::imageBoxScale($img,$fact1);
            $image1 = ExactImage::encodeImage($img,"jpeg",$jpegqual);
          }
          $image1 = $dbh->quote($image1);
          my $sql="update $db1.archivbilder set Bild=$image1 where Seite=$nr";
					$dbh->do($sql);
					ExactImage::deleteImage($img);
				}
			}
			$aktnr++;
		}
  }
}

