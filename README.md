ttyrec2
=======

This is the same as ttyrec but has something called "ttyrec2" mode that makes
ttyrec2 files. Ttyrec2 file is the same as an ordinary ttyrec file but it also
records input.

Ttyrec2 files are not compatible with ttyrec files.

What is ttyrec?
---------------

Ttyrec records terminal sessions, somewhat similar to the UNIX `script` tool.
Several roguelike communities record games using ttyrec. Ttyplay, included
with this software, can be used to playback the records. There are also other
ttyrec players such as termplay, ipbt and jettyplay.

Usage
-----

Use like ttyrec but if you want to record ttyrec2 instead, use `-2` command
line switch:

    ttyrec -2 [other options]

This by itself does not record input. If you want that, pass `-i` as well:

    ttyrec -2 -i [other options]

Conversion
----------

You can convert ttyrec2 to plain ttyrec files with the ttyrec2\_to\_ttyrec tool
that is included with this software.

CTRL+B hack
-----------

Now, it would be embarrassing if you recorded things like passwords to your
ttyrec2 files and sent them to someone. I've added a stupid hack so you can
avoid embarrassment. If you press CTRL+B while recording, it will turn off
input recording and give a message about it (and that message may or may not
mess up your screen a bit).

License
-------

Ttyrec is licensed under the BSD license with the advertising clause (bizarrely
enough). See ttyrec.c top comments.

