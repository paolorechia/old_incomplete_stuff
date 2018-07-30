#!/usr/bin/perl

use strict;
use warnings;

if ($#ARGV + 1 < 1){
    exit
}

print "$ARGV[0]\n";

my $saida;
$saida=$ARGV[0];

if ($saida=~ /(^[0-2][0-4]|^[0-1][0-9]):([0-5][0-9]$)/){
    print "Horas: $1\n";
    print "Minutos: $2\n";
}
else{
    if ($saida=~ /(^0[0-9]|^1[0-2]|^[0-9])(([aA]|[pP])[mM]$)/){
        print "Horas: $1\n";
        print "Periodo: $2\n";
    }
    else{
        if($saida=~ /(^0[0-9]|^1[0-2]|^[0-9]):([0-5][0-9])(([aA]|[pP])[mM]$)/){
        print "Horas: $1\n";
        print "Minutos: $2\n";
        print "Periodo: $3\n";
        }
        else{
            print "Tempo invalido\n";
        }
    }
}
