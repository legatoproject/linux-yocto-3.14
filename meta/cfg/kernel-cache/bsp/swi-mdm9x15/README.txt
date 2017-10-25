Oct 24, 2017
Dragan Marinkovic (dmarinkovi@sierrawireless.com)

To try to minimize confusion related to inclusion of various files,
avoid compatibility problems between Yocto version, and to be able
to get an idea what is the "final" kernel configuration without
actually building the kernel, we'll settle for few files:

* swi-mdm9x15-standard.scc - includes swi-mdm9x15.scc
* swi-mdm9x15.scc - includes swi-mdm9x15.cfg
* swi-mdm9x15.cfg - full kernel 3.14 configuration file

If you need to add/change kernel configuration, please do it
in swi-mdm9x15.cfg .
