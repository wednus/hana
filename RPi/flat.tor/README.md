Introduction
=
This demo automatically create a Tor container at host and provides capability hiding the real IP.

Installation
=
Run prep.sh, and login using the host's password.

Expected sample result output:

    IP (original): 76.xxx.xxx.xxx
    IP (torred): 130.149.80.199

Usage
=
    curl --socks http://host:9050 -L http://ifconfig.me