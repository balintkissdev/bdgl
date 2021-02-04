#!/usr/bin/env python


# Copyright (c) 2016 Balint Kiss <balint.kiss.501@gmail.com>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.


# TODO: Have option for obtaining Open Watcom V2 source
# TODO: Clean up code


import argparse
import errno
import os
import shutil
import stat
import sys
import urllib.request
import tarfile
import zipfile


class ConsoleColors:
    """
    Enumeration of console colors.
    """
    SUCCESS = '\033[92m'
    FAIL = '\033[91m'
    END = '\033[0m'


class Package:
    """
    Data structure representing a donwloadable package.

    name                -- Name of the package to identify with.
    url                 -- URL of the package to download from.
    long_name           -- Long name to display in descriptions.
    extension           -- Extension of compressed package, like .zip or .tar.gz.
    post_unpack_command -- Additional command to execute after unpacking.
                           (optional)
    description         -- Package description to display in the help menu.
                           (default "")
    extracted_name      -- New name to be extracted with on the disk.
                           (default "")
    bomb                -- Specifies if the package is a "bomb", meaning that
                           the contents of the package are not organized under
                           a package root folder. (default False)
    """

    def __init__(
            self,
            name,
            url,
            long_name,
            extension,
            post_unpack_command=None,
            description="",
            extracted_name="",
            bomb=False
    ):
        self.name = name
        self.url = url
        self.long_name = long_name
        self.extension = extension
        self.post_unpack_command = post_unpack_command
        self.description = description
        self.extracted_name = extracted_name
        self.bomb = bomb


def post_open_watcom_v2_unpack_command(package, path):
    # chmod u+x on Watcom binaries if under Linux/Unix
    if (
        sys.platform.startswith('linux') or
        sys.platform.startswith('freebsd') or
        'darwin' == sys.platform
    ):
        x86_bindir = path + '/binl/'
        x86_executable_list = os.listdir(x86_bindir)
        for executable_name in x86_executable_list:
            if "." not in executable_name:
                executable_path = x86_bindir + executable_name
                executable_stats = os.stat(executable_path)
                os.chmod(executable_path,
                         executable_stats.st_mode | stat.S_IXUSR)

        x64_bindir = path + '/binl64/'
        x64_executable_list = os.listdir(x64_bindir)
        for executable_name in x64_executable_list:
            if "." not in executable_name:
                executable_path = x64_bindir + executable_name
                executable_stats = os.stat(executable_path)
                os.chmod(executable_path,
                         executable_stats.st_mode | stat.S_IXUSR)
    else:
        log_package(package, "Not on Linux/Unix system, so there's nothing to "
                             "do."
                    )


PACKAGE_WATCOM_V2 = Package(
    name='open-watcom-v2',
    url="https://github.com/open-watcom/open-watcom-v2/releases/download/Current-build/ow-snapshot.tar.gz",
    long_name="Open Watcom V2 C/C++ compiler suite",
    extension='.tar.gz',
    post_unpack_command=post_open_watcom_v2_unpack_command,
    description="This is the C/C++ compiler used to build the library for "
                "16- and 32-bit DOS targets. It's the binary release, so you "
                "won't have to build the compiler itself.",
    extracted_name="open-watcom-v2",
    bomb=True
)

PACKAGE_DOS32A = Package(
    name='dos32a',
    url="http://download.narechk.net/dos32a-912-bin.zip",
    long_name="DOS32/A DOS extender",
    extension='.zip',
    description="This is the DOS extender used to execute 32-bit applications "
                "on DOS.",
    bomb=True
)

AVAIBLE_PACKAGES = {
    PACKAGE_WATCOM_V2.name: PACKAGE_WATCOM_V2,
    PACKAGE_DOS32A.name: PACKAGE_DOS32A
}


def create_deps_dir():
    """
    Create the "deps" folder in the project root if it does not exists yet.
    """
    if os.path.exists(DEPS_DIR):
        print("\"deps\" folder already exists", flush=True)
        return

    try:
        print("Creating \"deps\" folder ...", flush=True)
        os.makedirs(DEPS_DIR)
        print(ConsoleColors.SUCCESS + "Done." + ConsoleColors.END, flush=True)
    except OSError as e:
        if errno.EEXIST != e.errno:
            raise


SCRIPT_DESCRIPTION = "Download and install dependencies of BDGL into the " \
                     "\"deps\" folder of the project."

SCRIPTS_DIR = os.path.dirname(os.path.realpath(__file__))
PROJECT_DIR = os.path.dirname(SCRIPTS_DIR)
DEPS_DIR = os.path.join(PROJECT_DIR, "deps")


def log_package(package, message, status=''):
    """
    Log status of the package in the following format:

    [package name]: message

    status   -- Status of the message with color (default '')
    packages -- Package object to log.
    message  -- Message to log.
    """
    print(status + "[" + package.name + "]: " + message + ConsoleColors.END,
          flush=True)


def install_all(packages, force=False):
    """
    Install all specified packages.

    packages -- List of Package objects to install.
    force    -- Force remove and reinstall packages. (default False)
    """
    for p in packages:
        install(p, force)


def install(package, force=False):
    """
    Install a specified package.

    package -- Package object to install.
    force   -- Force remove and reinstall package. (default False)
    """
    if force:
        try:
            log_package(package, "Force install: removing...")
            os.remove(os.path.join(DEPS_DIR, package.name + package.extension))
            shutil.rmtree(os.path.join(DEPS_DIR, package.name))
            log_package(package, "Removing completed.")
        except OSError as e:
            if errno.ENOENT != e.errno:
                raise
    elif not force and os.path.isdir(os.path.join(DEPS_DIR, package.name)):
        log_package(package, "Package already exists. Skipping...")
        return

    download(package)
    extract(package)


def download(package):
    """
    Download a specified package.

    package -- Package object to download.
    """
    # TODO: Show a progressbar
    log_package(package, "Downloading from " + package.url)
    downloaded_file = os.path.join(DEPS_DIR, package.name + package.extension)

    urllib.request.urlretrieve(package.url, downloaded_file)

    log_package(package, "Download is completed!", ConsoleColors.SUCCESS)


def extract(package):
    """
    Extract a specified package.

    package -- Package object to extract.
    """
    log_package(package, "Extracting files...")

    package_path = os.path.join(DEPS_DIR, package.name)
    if package.bomb:
        unpack_path = package_path
    else:
        unpack_path = DEPS_DIR

    if package.extension == '.zip':
        zip_file = zipfile.ZipFile(package_path + package.extension, 'r')
        zip_file.extractall(unpack_path)
        zip_file.close()
    elif package.extension == '.tar.gz':
        tar_file = tarfile.open(package_path + package.extension, 'r:gz')
        tar_file.extractall(unpack_path)
        tar_file.close()
    else:
        log_package(package, "Unsupported package format!", ConsoleColors.FAIL)

    if '' != package.extracted_name:
        extracted_file = os.path.join(DEPS_DIR, package.extracted_name)
        to_rename = os.path.join(DEPS_DIR, package.name)
        os.rename(extracted_file, to_rename)

    log_package(package, "Extracting files is completed!",
                ConsoleColors.SUCCESS)

    if package.post_unpack_command is not None:
        log_package(package, "Executing post-unpack commands...")
        package.post_unpack_command(package, package_path)
        log_package(package, "Post-unpack command execution is completed!",
                    ConsoleColors.SUCCESS)


def read_arguments():
    """
    Read command line arguments.
    """
    arg_parser = argparse.ArgumentParser(
        description=SCRIPT_DESCRIPTION,
        formatter_class=argparse.RawDescriptionHelpFormatter,
        # HACK: Only way not to show package argument group in usage
        usage='%(prog)s [-h] [-f] [-t  [...]]'
    )
    arg_parser.add_argument(
        '-f',
        '--force',
        help="Force delete, redownload end extract dependency. "
             "If no packages were specified after the -t or --target option, "
             "all packages will be reinstalled.", action='store_true'
    )
    arg_parser.add_argument(
        '-t',
        '--target',
        choices=AVAIBLE_PACKAGES.keys(),
        help="Install or apply actions only to the specified dependencies.",
        metavar='',
        nargs='+'
    )
    targets = arg_parser.add_argument_group(
        description="The following values can be used "
                    "with the -t or --target option:"
    )
    for p in AVAIBLE_PACKAGES.values():
        targets.add_argument(
            p.name,
            help=p.long_name + ". " + p.description,
            nargs='?'
        )

    return arg_parser.parse_args()


def main():
    args = read_arguments()
    packages_to_install = []
    if args.target:
        for t in args.target:
            if t in AVAIBLE_PACKAGES:
                packages_to_install.append(AVAIBLE_PACKAGES[t])
    else:
        packages_to_install = AVAIBLE_PACKAGES.values()

    create_deps_dir()
    install_all(packages_to_install, args.force)


if "__main__" == __name__:
    main()
