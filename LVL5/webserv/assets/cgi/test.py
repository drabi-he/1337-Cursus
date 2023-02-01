#!/usr/bin/python

# Import CGI and CGIT module
import cgi, cgitb

# to create instance of FieldStorage
# class which we can use to work
# with the submitted form data
form = cgi.FieldStorage()
your_name = form.getvalue('your_name')

# # to get the data from fields
company_name = form.getvalue('company_name')

print ("<html>")
print ("<head>")
print ("<title>First CGI Program</title>")
print ("</head>")
print ("<body>")
print ("<link rel=\"stylesheet\" href=\"./style.css\">")
print ("<div class=\"container\">")
print ("<a href=\"/\"><h1>WebServ</h1></a>")
print ("<p>CGI Python Test</p>")
print ("<h2>Hello, %s is working in %s</h2>"
	% (your_name, company_name))

print ("</body>")
print ("</html>")
