# diary-engine
An engine with simple API to manage simple logs / diaries / journals.

The idea is to save the diaries in plain text (possibly encrypted in future
version). Thus keeping them readable without any special software. Multimedia
will be encoded with base64. Furthermore, there is support for keyword 
and fulltext search (eventually).

Each book (diary) will be a directory, holding entries in subdirectories named
by <year>/<month>/<day>/. The entries will be formatted as email messages, as
defined in RFC 5322 with the exception that UTF-8 will be used for all plain
text, even in the "headers". Multimedia attachments are included as defined 
in RFC 2045-2049 (MIME). Thus, example entry file would be:

From: "Author Name" <author@domain.com>
Date: 2000-10-10T10:00+0200
Message-ID: <<uuid transformed into an integer>@domain.com>
Subject: <entry title>
Content-Type: <text/plain, multipart/mixed or other relevant mimetype>; 
        boundary="proper boundary"

--proper boundary
Content-type: text/plain; charset="UTF-8"
this is text, äöly!

--proper boundary
Content-type: image/jpeg; name="whatever.jpg"
Content-Disposition: Attachment; filename="whatever.jpg"
Content-transfer-encoding: base64

<loads of encoding>
--proper boundary--
