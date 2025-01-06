# Android Documentation

This tutorial shows you how to use Brawermaker on Android.

## Termux Installation

First [download the APK](https://dl.natesworks.com/tools/termux/termux.apk). After it finishes downloading press `Open` if it is your first time installing an app from your browser grant it the necessary permissions. After that press `Install`.

## Installing brawlermaker

### Installing wget

To easily download brawlermaker you can use `wget`. Download it using the following command:

```sh
pkg in wget
```

### Downloading brawlermaker

To download brawlermaker simply fetch it using `wget`.

```sh
wget https://dl.natesworks.com/tools/brawlermaker/linux/arm64/bm
```

If you don't have aarch64 but rather arm run this instead

```sh
wget https://dl.natesworks.com/tools/brawlermaker/linux/arm/bm
```

### Moving to bin directory

Now simply move it to `bin` (the place where you store binaries on linux) using the following command:

```sh
mv bm $PREFIX/bin
```

## Grant execute permissions

To run a binary on linux you must grant it execute permissions.

```sh
chmod +x $PREFIX/bin/bm
```

## Setting up storage

To access your documents (where you have the base Brawl Stars APK) you can setup storage.

```sh
termux-setup-storage
```

Now copy the base mod from `storage/documents`.

## Fixing "Bad system call"

**Credits:** burned kenji

### Install proot

```sh
pkg in proot
```

### Enter proot

```sh
termux-chroot
```

## Finished

You can now use brawlermaker by running the `bm` command!
