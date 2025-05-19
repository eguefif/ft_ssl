# Ft_ssl
This project is a learning project based on the 42 projects. The goal is to learn about hashing algorithm and encryption.

This program can generate sha2-256 and md5 hash. There is an input limit of 50000 char.

# How to use it

```bash
make
./ft_ssl md5 FILENAME
./ft_ssl sha256 FILENAME
echo -n STRING | ./ft_ssl md5
```
You can use the following flag:
* -q: quiet, display only the digest
* -r: reverse the digest and filename display
* -p: display the content of stdin

# Todo
- [ ] Impl DES algo

# Testing
I use CUnit. Here is how to install the framework.
```bash
sudo apt-get install libcunit1 libcunit1-doc libcunit1-dev
```

How to use it
```bash
make test_md5
make test_sha256
```

# Author
Emmanuel Guefif

