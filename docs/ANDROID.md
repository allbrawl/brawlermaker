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
wget https://dl.natesworks.com/tools/brawlermaker/android/bm
```

### Moving to bin directory

Now simply move it to `bin` (the place where you store binaries on linux) using the following command:

```sh
mv bm $PREFIX/bin
```

## Setting up storage

To access your documents (where you have the base Brawl Stars APK) you can setup storage.

```sh
termux-setup-storage
```

Now copy the base mod from `storage/documents`.

## Finished

Now you can use brawlermaker by using the `bm` command.
