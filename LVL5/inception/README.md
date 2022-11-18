# Basic Tips & Instructions

## 1. Run a basic Docker container in interactive mode

	docker run -it -p `[host_port]:[container_port]` `[image]:[tag]`

> for this project, either `debian:buster` or `alpine:latest`

**FLAGS:**
  - `-i`: interactive mode (Keep STDIN open even if not attached)
  - `-t`: terminal mode (Allocate a pseudo-tty)
  - `-p`: port mapping

### 2. Try to setup the service from scratch

### 3. after you finish the setup successfully, create a Dockerfile

	FROM [image]:[tag]
	RUN [command]
	[...]
	COPY [source] [destination]
	[...]
	EXPOSE [port]
	CMD [command]

<details>
<summary>NGINX</summary>

### 1. First update the package list

**debian:buster**
	apt update -y && apt upgrade -y

**alpine:latest**
	apk update && apk upgrade


### 2. Install NGINX and OpenSSL

**debian:buster**
	apt install -y nginx openssl

**alpine:latest**
	apk add nginx openssl

### 3. Create a self-signed certificate

	openssl req -x509 -new -newkey rsa:2048 -nodes -keyout /etc/ssl/private/localhost.key -out /etc/ssl/private/localhost.crt -subj "/C=MA/ST=Beni Mellal-Khenifra/L=Khouribga/O=42 Network/OU=IT/CN=localhost"

**FLAGS**
  - `req`: creates and processes certificate requests
  - `-x509`: generate a self-signed certificate
  - `-new`: create a new certificate request
  - `-newkey rsa:2048`: create a new private key using RSA and 2048 bit
  - `-nodes`: no passphrase/password (not encrypted)
  - `-keyout`: output the private key to a file
  - `-out`: generate the certificate to a file (*.crt/*.csr)
  - `-subj`: provide the certificate information
  	- `/C`: Country Name (2 letter code)
  	- `/ST`: State or Province Name (full name)
  	- `/L`: Locality Name (eg, city)
  	- `/O`: Organization Name (eg, company)
  	- `/OU`: Organizational Unit Name (eg, section)
  	- `/CN`: Common Name (eg, your name or your server's hostname)

> for more detailed information about the `openssl req` command, check [this](https://www.openssl.org/docs/man1.1.1/man1/openssl-req.html)

### 4. Create a new NGINX configuration file

	vim /etc/nginx/nginx.conf
> (e.g : [here](./alpine/srcs/requirements/nginx/conf/nginx.conf))

important : check if the configuration file is valid by running `nginx -t`

### 5. Create the files you want to serve

	vim [path]/index.html
> (e.g : [here](./alpine/srcs/requirements/nginx/tools/index.html))

> **important : the path is the same as the one you specified in the NGINX configuration file**

### 6. Start the NGINX service

**debian:buster**
	service nginx start

**alpine:latest**
	nginx

### 7. Test the service

from your host machine, open your browser and go to `https://localhost:[host_port]`

### 8. Additional Tips

**check if nginx compatible with TSLv1.2 and TLSv1.3**
 - curl -I -v --tlsv1.1 --tls-max 1.1 `https://localhost:[host_port]` -k // should fail
 - curl -I -v --tlsv1.2 --tls-max 1.2 `https://localhost:[host_port]` -k // should pass if you have TSLv1.2
 - curl -I -v --tlsv1.3 --tls-max 1.3 `https://localhost:[host_port]` -k // should pass if you have TSLv1.3

if you get `The plain HTTP request was sent to HTTPS port`
try sending request to https instead of http

</details>