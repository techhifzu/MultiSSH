# MultiSSH
MultiSSH is a systems administration tool that runs Linux/Unix commands on multiple ssh servers, it is a lightweight tool that is easy to setup and use.

Setup
-----

Install dependencies for Debian/Ubuntu, run in your Terminal shell:

```shell
sudo apt-get install libssh-dev
```
Or for Red Hat/CentOS:
```shell
sudo yum install libssh-devel
```
Then compile:
```shell
gcc multissh.c -o multissh -lssh
```
Usage instructions
------------------
You must create a file named 'sshservers' which contains a list of ssh servers and credentials before MultiSSH is run, you must add one line per server, in the format:

sshserverhost:sshserverport:sshserverusername:sshserverpassword

The sshservers.example file is an example of what an 'sshservers' file should look like.

After compiling, MultiSSH can be run as follows:

```shell
./multissh 'command(s)'
```
When running multiple commands, each command must be separated with a semicolon ';' and all commands must be within quotes, for example:
```shell
./multissh 'ps; free -m'
```
Tested and confirmed working on Ubuntu, CentOS, and OS X. Should work on any Linux distribution and *BSD.
