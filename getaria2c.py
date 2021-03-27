#!/usr/bin/env python3
import argparse
import sys
import os
import urllib.request


def download_content(url, dst):
    req = urllib.request.Request(url, headers={
        "Referer": url,
        "User-Agent": "Mozilla/5.0 (Macintosh; Intel Mac OS X 11_2_3) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/89.0.4389.90 Safari/537.36",
    })
    with open(dst, "wb") as f:
        with urllib.request.urlopen(req) as rsp:
            f.write(rsp.read())


LINUX_URL = ""
OSX_URL = "https://raw.githubusercontent.com/ko-han/hunt/master/aria2c/aria2c-1.35.0-osx-darwin"
WIN32_URL = "https://raw.githubusercontent.com/ko-han/hunt/master/aria2c/aria2c-1.35.0-win-32.exe"
WIN64_URL = "https://raw.githubusercontent.com/ko-han/hunt/master/aria2c/aria2c-1.35.0-win-64.exe"

platform_map = {
    "darwin": OSX_URL,
    "win32": WIN32_URL,
    "linux": LINUX_URL,
}


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--platform", help="platform specific", choices=list(platform_map.keys()))
    parser.add_argument("--out-directory", help="out directory", default=".")
    args = parser.parse_args()
    if not args.platform:
        args.platform = sys.platform
    url = platform_map.get(args.platform)
    if not url:
        raise RuntimeError("unsupported platform: %s" % sys.platform)
    download_content(url, os.path.join(args.out_directory, "aria2c"))


if __name__ == '__main__':
    main()
