#!/usr/bin/perl

use LaTeX::Decode;
use Encode;

$LaTeX::Decode::DefaultScheme = 'full';
while (<>) {
    # replace \, with \d{}
    $_ =~ s/\\,([a-zA-Z])/\\d{\1}/g;

    # decode latex accents
    $_ = encode_utf8(latex_decode($_));

    $_ =~ s/---/—/g;
    $_ =~ s/--/–/g;

    print;
}
