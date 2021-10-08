# MultiSSH
MultiSSH is a systems administration tool that runs Linux/Unix commands on multiple ssh servers, it is a lightweight tool that is easy to setup and use.

Setup
-----

Install dependencies for Debian/Ubuntu, run in your Terminal shell:

sudo apt-get install libssh-dev

Or for Red Hat/CentOS:

sudo yum install libssh-devel

Then compile:
gcc multissh.c -o multissh -lssh

Usage instructions
------------------
You must create an 'sshservers' file with a list of ssh servers and credentials before MultiSSH is run, you must add one line per server, in the format:

sshserverhost:sshserverport:sshserverusername:sshserverpassword

example contents of a 'sshservers' file:

127.0.0.1:22:root:RoorToorRootToor
192.168.0.254:22222:user:AGreatLongPassphrase
localhost.localdomain:1234:root:AnEvenLongerPassphrase
example.org:22:root:G@OHBUOn4hm2n

After compiling, MultiSSH can be run as follows:

./multissh 'command(s)'

When running multiple commands, each command must be separated with a semicolon ';' and all commands must be within quotes, for example:

./multissh 'ps; free -m'

Tested and confirmed working on Ubuntu, CentOS, and OS X. Should work on any Linux distribution and *BSD.
