############
diary-engine
############

-----
Intro
-----

An engine with simple API to manage simple logs / diaries / journals.
The project uses Qt framework to implement the functionality, but the
API only needs the C++ standard library. 

So to use the library, you will
need to dynamically link against Qt binaries, but you don't need the Qt
development packages after you have obtained (compiled) binaries for the
diary engine. (It is in consideration to eventually change the implementation
to be self-sufficient and dependent only on C++ standard library).

The idea is to save the diaries in plain text (possibly encrypted in future
version). Thus keeping them readable without any special software. Multimedia
will be encoded with base64. Furthermore, there is support for keyword 
and fulltext search (eventually).

Each book (diary) will be a directory. The entries will be formatted as 
email messages, 
thus enabling reading with an email client, for simplified multimedia 
viewing. The format used is as defined in RFC 5322 with the exception that 
UTF-8 will be used for all plain text, even in the "headers". Multimedia 
attachments are included as defined in RFC 2045-2049 (MIME). 

Thus, example entry file would be:

From: "Author Name" <author@domain.com>
Date: 2000-10-10T10:00:00+02:00
Message-ID: <<uuid transformed into an integer>@<journal name>>
Subject: <entry title>
X-Engine-Version: x.x
X-Entry-Keywords: again,me,test
Content-Type: multipart/mixed; 
        boundary="proper boundary"

--proper boundary
Content-Type: text/plain; charset="UTF-8"

this is text, äöly!

--proper boundary
Content-Type: image/jpeg; name="whatever.jpg"
Content-Disposition: Attachment; filename="whatever.jpg"
Content-Transfer-Encoding: base64

<loads of encoding>

--proper boundary--

--------
Building
--------

The library depends on a few Qt core libraries, so you will need
to install the Qt framework to compile. (Exact dependencies to be
added later).

The project uses Qt build system, qmake, to generate Makefiles.
To build, run:

qmake
make

-------
Testing
-------

NOTE: Tests currently only work on *nix systems, as it is assumed
that /tmp/ exists and is writable. Most of the tests are unit tests,
but some of them use file IO and so on, which should not be present
in "proper" unit tests, but as a part of integration tests. Nevertheless,
 I did not deem this necessary for this small project.

The automated tests are made using the cxxtest-framework.
To generate and compile the tests, you need to install it. Most
Linux distributions have a package for it. More information at 
http://cxxtest.com/.

After compiling, you can run the unit tests from
the repository root using

env LD_LIBRARY_PATH=src/ test/test

