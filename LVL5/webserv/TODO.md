# CHECKS

- key with multiple value
- duplicate key
- duplicate error codes
- empty values
- wrong value format
- how to change the host ip

# LISTEN

- default host is localhost {127.0.0.1}
- default port is 80
- 1 ≤ port ≤ 65535
- if duplicate it use all the values
- values can't be duplicated

# SERVER NAME

- can take multi values

# ROOT

- root is mandatory if no `location` exist
- the path of the files you want to serve

# INDEX

- default index.html
- it change the default page for `root`
- in case of multi values or duplicate it uses the first one it found in order;
- if none exist {error 403}

# AUTO INDEX

- default off
- turn directory listing on/off
- if off return 404 if no index.html is found

# CLIENT MAX BODY SIZE

- if the request body exceeds it {error 413}
- default 1m
- disable check if value is 0

# ERROR PAGE

- if response status code equal values redirect to custom page
- can take multi status code but only one custom page
- can change response status code
- 300 ≤ value ≤ 599
- if value is duplicate use the first one

# LOCATION

- can't duplicate path

# RETURN { REDIRECTION }

- status code and url
- url isn't mandatory
- status code should be valid

# CAN'T TAKE MULTIPLE PARAMETERS

- listen
- root
- autoindex
- client_max_body_size

# CAN'T BE DUPLICATED

- root
- autoindex
- client_max_body_size

# HTML STATUS CODE

- 307 : Temporary Redirect
- 308 : Permanent Redirect

# ADDED PROPERTY

- upload_path
- methods
