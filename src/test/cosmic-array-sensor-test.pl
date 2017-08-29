#!/usr/bin/perl -w

# Test the cosmic array sensor by randomly triggering interupts on the
# GPIO lines.

$|=1;

use Time::HiRes qw(usleep);

# Create random events
my $debug  = 0;
my $dryrun = 0;

my @events             = [0,1,2,3]; # Pins to toggle
my $delay_mean         = 10000000; # Microseconds (10s)
my $delay_variance     =  9000000; #

my $cmd = "";

sub event_distribution {
    my $event;
    $event = int(rand(3));

    return $event;
}

sub delay_distribution {
    my ($mean, $variance) = @_;

    my $vary = int(rand(2 * $variance) - $variance);
    my $delay = $mean + $vary;
    
    return $delay;
}

while(1){

    my $delay = delay_distribution($delay_mean, $delay_variance);
    my $event = event_distribution();

    print "Delay: $delay Event $event ";

    $cmd = "gpio mode $event up";
    print $cmd,"\n" if $debug;
    print "u";
    `$cmd` unless $dryrun;

    $cmd = "gpio mode $event down";
    print $cmd,"\n" if $debug;
    print "d";
    `$cmd` unless $dryrun;

    print "\n";

    usleep($delay);
}

