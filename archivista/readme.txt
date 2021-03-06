This is initial mirror of the Archivista SVN. To find out more about archivista, please visit
www.archivista.ch

Original readme.txt
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

The whole source code of the ArchivistaBox software project is under GPLv2. You
won't find a note on any file, but everything under /home/cvs as well under
/home/archivista is GPLv2 code (the code is not compiled, it is Perl/PHP).

The projects we use inside of the ArchivistaBox are:

- ExactImage (GPLv2) & hocr2pdf (GPL2), see http://www.exactcode.de
- Wine (LGPLv2, not needed for OS text recognition), http://www.winehq.org
- T2 project (Linux system), see http://www.t2-project.org
- Sane (GPLv2 + LGPLv2), see http://www.sane-project.org
- Cuneiform (BSD), see https://launchpad.net/cuneiform-linux

You won't find this code on the ArchivistaBox itself, but we are having our eyes
on it that the source code is available. Should it not be available, please let
us know and we will fight for it that you can download it under the appropriate
licence (or then publishing it on our page).

Concerning compiling the whole ArchivistaBox CDs it is rather a complex story.
You can checkout T2 project code (www.t2-project.org) and then use the
ArchivistaScan Station target. After it a lot of sourcecode will be downloaded
and compiled. At the end you will need about some 20 GByte for the whole system.
On a dual core machine it needs some days to create the full CD.

We are using some older kernels, I won't recommend to you to build them too,
just start somewhere with 2.6.26 kernel or newer.

Please find below the package target list from T2, but you find this also on the
ArchivistaScan station target in T2 (/t2-trunk/target/archivista/pkgsel):

<<<<<<<<<<<<<<<<<<<
# Package selection for the Archivista Box

O *

X 00-dirtree
X a2ps
X acl
X acpid
X adaptec-usbxchange
X afio
X apache
X apmd
X apr
X apr-util
X arts
X at
X atk
X attr
X autoconf
x automake
X bash
X bc
X bdb
X bdb33
X biff+comsat
X bin86
X binutils
X bison
X bitstream-vera-fonts
X bzip2
X ccache
X coreutils
X cpio
X cracklib
X cron
X cups
X cups-pdf
X curl
X cvs
X dbus
X ddcxinfo
X dhcp
X dialog
X dietlibc
X diffstat
X diffutils
X disktype
X distcc
X dmalloc
X docbookx
X dosfstools
X e2fsprogs
X ed
X eject
X electricfence
X elf
X embutils
X enscript
X epeg
X escreen
X ethtool
X evas
X exim
X expat
X expect
X fam
X fbset
X fetchmail
X file
X findutils
X firefox
X flex
X flexbackup
X fluxbox
X freefonts
X freetype
X freetype1
X fribidi
X gawk
X gcc
X gconf
X gconf-editor
X gdb
X gdbm
X gdm
X gettext
X ghostscript
X ghostscript-fonts
X gkrellm
X gle
X glib
X glib12
X glibc
X glut
X gmp
X gnome-icon-theme
X gnome-keyring
X gnome-mime-data
X gnome-vfs
X gnupg
X gperf
X gpm
X grep
X groff
X grub
X gsl
X gtk+
X gtk+12
X gtk-engines
#X gv
X gzip
X hal
X hdparm
X hicolor-icon-theme
X hotplug
X hotplug++
X htmldoc
X id-utils
X inotify-tools
X imagemagick
X imager
X imlib
X indent
X input-utils
X intltool
X iproute2
X iptables
#X jfsutils
X jhead
X jpeg2ps
X kbd
X kdebase
X kdegraphics
X kdelibs
X kiss
X ksymoops
X lcap
X lcms
X less
X lesstif
X libart_lgpl23
X libbonobo
X libbonoboui
X libcap
X libcroco
X libdaemon
X libelf
X libgd
X libglade
X libglade10
X libgnome
X libgnomecanvas
X libgnomeui
X libgsf
X libidl
X libidn
X libjpeg
X liblockfile
X libmng
X libol
X libpcap
X libpng
X libraw1394
X librep
X librsvg
X libsafe
X libsdl
X libtiff
X libtool
X libungif
X libunicode
X libusb
X libvncserver
X libxml
X libxml++
X libxml1
X libxslt
X linux-header
X linux26
X lm_sensors
X lrzsz
X lsof
X ltrace
X lzo
X m4
X mailx
X make
X man
X man-pages
# X matrox-mtx
X memtest86
X microcode_ctl
X minised
X miscfiles
X mktemp
X mmv
X mod_perl
X module-init-tools
X modutils
X mouseemu
X mozplugger
X mtr
X mt-st
X mysql
X nasm
X ncompress
X ncurses
X neon
X net-tools
X neutral
X netkit-base
X netkit-ftp
X netkit-ntalk
X netkit-routed
X netkit-rsh
X netkit-telnet
X netpbm
X nfs-utils
X nssdb
# X nvidia
X openssh
X openssl
X orbit10
X orbit2
X pam
X pango
X parted
X patch
X patchutils
X pciutils
X pcmcia-cs
X pcre
X pdfjam
X pdftk
X pdksh
X perl
X perl-xml-parser
X perl-dbd-mysql
X perl-crypt-des
X perl-digest-md5
X perl-digest-hmacmd5
X perl-image-size
X perl-mail-sendmail
X perl-mime-base64
X perl-dbi
X perl-gd-graph3d
X perl-error
X perl-text-autoformat
X perl-pod-pom
X perl-image-info
X perl-text-reform
X perl-tie-dbi
X perl-xml-libxslt
X perl-xml-xpath
X perl-xml-regexp
X perl-appconfig
X perl-cgi-ajax
X perl-carp-clan
X perl-convert-asn1
X perl-authen-sasl
X perl-net-ldap
X perl-latexml
X perl-xml-dom
X perl-test-manifest
X perl-parse-recdescent
X perl-html-tagset
X perl-class-accessor
X perl-xml-rss
X perl-xml-libxml-xpathcontext
X perl-date-calc
X perl-bit-vector
# perl-mail-box and deps
X perl-uri
X perl-libwww
X perl-mime-types
X perl-io-stringy
X perl-user-identity
X perl-mailtools
X perl-mail-box
# more perl
X perl-ui-dialog
X perl-reform
X perl-html-table
# perl pop3/imap
X perl-net-ssleay
X perl-io-socket-ssl
X perl-mail-imapclient
X perl-mail-pop3client
X perl-digest-hmacmd5
X prima
X ipa
X pkgconfig
X popt
X portmap
X potrace
X ppp
X procinfo
X procmail
X procps
X psmisc
X psutils
X python
X qt
X rcs
X readline
X recode
X rng-tools
X rsync
X sane-backends
X sane-frontends
X screen
X scrollkeeper
X sed
X serpnp
X setserial
X shadow
X shared-mime-info
X sharutils
X slang
X smartmontools
X squashfs-tools
X startup-notification
X strace
X subversion
X sudo
X swig
X sysfiles
X sysfsutils
X sysklogd
X sysstat
X sysvinit
X tar
X tcl
X tcp_wrappers
X tcsh
X tetex
X texinfo
X tiff2png
X time
X tk
X tree
X udev
X unionfs
X units
X unrar
X unzip
X usbutils
X util-linux
X uudeview
X vim
X vnc
X vsftpd
X wdiff
X wine
X wireless-tools
X x11vnc
#X xaw3d
X xdialog
#X xfsprogs

# modular X.org X11R7
# needed by xsm
X netkit-rsh

# the basic modular X.org tree

X xorg/*proto*
X xorg/*ext
X xorg/*lib*
= xorg/*xf86-*
# but only the most common input drivers
O xorg/xf86-input*
X xf86-input-keyboard
X xf86-input-evdev
X xf86-input-evtouch
X xf86-input-mouse
X xf86-input-synaptics
X xf86-input-mouse
X xf86-input-vmmouse

# no xcb, yet
O xcb-proto
O libxcb
O libpthread-stubs

X xorg/font-*
X fslsfonts
X fstobdf
X bdftopcf
X rgb
X xbitmaps
X mesa
X xorg-server
X xinit
X xrdb
X xauth
X iceauth
X fontconfig
X mkfontdir
X mkfontscale
X xcursorgen
X xcursor-themes
X xtrans
X libxau
X xcmiscproto
X xkbcomp
X xkbdata
X setxkbmap
X makedepend
X rman
X imake
X cf
X gccmakedep
X pixman

X xconsole
X xsm
X xhost
x xkill
X xdpyinfo
X xwininfo
X xrandr
X xmag
X xorg/xset*
X xev

X freetype*
X gle
X lesstif
X libgd
X netpbm
X xaw3d

# a display-, window-manager and terminal
X xdm
X xterm

# X.org selection END

X xpdf
X zip
X zlib
# contians av-xevie-sb
X 99-final

# sysfiles split
X stone
X mkinitrd
X rocknet

# only for gnomesu - maybe replace ...
X libzvt
X gnomesu

# system stress testing
X bonnie++
X cpuburn
X memtester

# cdburning
X cmake
X cdrkit
X dvd+rwtools

# remote shell test prowser
X links

X tesseract

# X ruby
# X rubygems

# WebGUI 5.8.8

X perl-html-parser
X perl-compress-zlib
X perl-io-zlib
X perl-archive-tar

# docutils (reStructuredText)

X docutils

X rdesktop

# X postgresql
# X perl-dbd-postgresql
X brscan
X hplip

X latex2html
X kile
X php

X exact-image

X aspell
X aspell-de
# X aspell-fr
X aspell-en
# X samba

# virtualization
X qemu
X kvm
>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
