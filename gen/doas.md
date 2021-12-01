# doas - the better alternative to sudo
10-27-21

## origin
doas comes from bsd, and has been
ported to linux in recent years.

## installation
doas comes in the repos for most linux
distros, and in the aur for arch users.
note that you will need to configure
it after installation.

## configuration
the config file for doas
is located at `/etc/doas.conf`
the file is structured as follows:

	# comments using hashes
	# man doas.conf(5)
	permit/deny options user as target cmd allowed_command args allowed_args

	# options:
	# nopass means that doas will not ask for a password.
	# nolog means doas will not write using sysklogd.
	# persist means don't require password after it is entered once.
	# keepenv means keep environment variables
	# setenv means set variables

	# if cmd and args are blank all commands are allowed
	# if args is blank but not cmd, no args can be passed

## why
sudo is bloated with many complicated
options and separate commands and config files.
doas is incredibly simple to configure and set up,
and i find it easier and better to use than sudo.

on most distros you'll have to keep sudo as a dependency,
but if you can get away with removing it (easily done on gentoo),
you can have a system free of sudo.
