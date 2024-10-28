#!/usr/bin/perl

use strict;
use warnings;
use CGI;

# Enable error output to the browser
use CGI::Carp qw(fatalsToBrowser);

my $cgi = CGI->new;

print $cgi->header('text/html');
print "<h1>Addition Results in perl</h1>";

# Retrieve the parameters
my $num1 = $cgi->param('num1');
my $num2 = $cgi->param('num2');

if (defined $num1 && defined $num2 && $num1 =~ /^\d+$/ && $num2 =~ /^\d+$/) {
    my $sum = $num1 + $num2;
    print "<output>$num1 + $num2 = $sum</output>";
} else {
    print "<output>Sorry, the script cannot turn your inputs into numbers (integers).</output>";
}