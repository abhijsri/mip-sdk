#!python
import sys
import platform as _platform
from os.path import expanduser

def IsRHEL():
    linux_distro = "".join(_platform.linux_distribution()[:2]).replace('.', '').lower()
    return linux_distro.startswith('centos linux7') or linux_distro.startswith('red hat enterprise linux server7')

Help("""
Run 'scons arch=ARCHITECTURE configuration=CONFIGURATION' to build.
    'scons --arch=ARCHTITECTURE to specify architecture. Choose from ['x86', 'x64']. (Default: 'x64')
    'scons --configuration=CONFIGURATION' to specify configuration. Choose from ['debug','release']. (Default: 'debug')
    'scons --msvc=MSVC' to specify msvc version (win32-only). Choose from ['14','12']. (Default: '14')
""")

#
# Architecture/platform (default: x64)

AddOption(
    '--arch',
    choices=['x86', 'x64'],
    help='Architecture: [x86, x64]',
    default='x64')

#
# Configuration/flavor (default: debug)

AddOption(
    '--configuration',
    choices=['debug','release'],
    help='Configuration: [debug, release]',
    default='debug')

#
# MSVC version (default: 14)

AddOption(
    '--msvc',
    choices=['14','12'],
    help='Configuration: [14, 12]',
    default='14')

build_arch = GetOption('arch')
build_flavor = GetOption('configuration')
msvc = GetOption('msvc')
platform = sys.platform

if platform == 'linux2':
    target_arch = 'x86_64'
elif platform == 'win32':
    target_arch = 'x86' if build_arch == 'x86' else 'amd64'
elif platform == 'darwin':
    osx_version_flag = '-mmacosx-version-min=10.10'
    target_arch = 'i386' if build_arch == 'x86' else 'x86_64'

CXXFLAGS_BASE = '-DELPP_THREAD_SAFE '
msvc_ver = ''

if platform == 'linux2':
    CXXFLAGS = CXXFLAGS_BASE + '-std=gnu++11 -D_REENTRANT -fPIC'
    if build_flavor == 'debug':
        CXXFLAGS = CXXFLAGS + ' -g -DDBG_ENABLED -DDEBUG -D_DEBUG'
    else:
        CXXFLAGS = CXXFLAGS + ' -O2 -DNDEBUG -DNDEBUG'
    LINKFLAGS = ''
elif platform == 'win32':
    CXXFLAGS = CXXFLAGS_BASE + '-FS -W3 -w34100 -w44251 -GR -EHsc -DUNICODE'
    LINKFLAGS = ' /DEBUG'
    if build_arch == 'x86':
        CXXFLAGS = CXXFLAGS + '-DWIN32'
    else:
        CXXFLAGS = CXXFLAGS + '-DWIN64'
    if build_flavor == 'debug':
        CXXFLAGS = CXXFLAGS + ' -c -MDd -DDEBUG -D_DEBUG'
    else:
        CXXFLAGS = CXXFLAGS + ' -c -O2 -MD -DNDEBUG -DNDEBUG'
    if msvc == '12':
        CXXFLAGS = CXXFLAGS + ' -DMSVC12'

    msvc_ver = msvc + '.0'

elif platform == 'darwin':
    CXXFLAGS = CXXFLAGS_BASE + osx_version_flag + ' -std=c++11 -stdlib=libc++'
    LINKFLAGS = osx_version_flag + ' -framework CoreServices'
    if build_flavor == 'debug':
        CXXFLAGS = CXXFLAGS + ' -DDEBUG -D_DEBUG -DDBG_ENABLED -g'
    else:
        CXXFLAGS = CXXFLAGS + ' -DNDEBUG -D_NDEBUG -O1 '

build_args = {
    "MSVC_VERSION": msvc_ver,
    "TARGET_ARCH": target_arch
}

#
# Additional variables required by constituent SConscripts

protection_supported_platforms = [ 'win32', 'linux2', 'darwin', 'android' ]
file_supported_platforms = [ 'win32', 'linux2', 'darwin' ]
is_file_sdk_enabled = platform in file_supported_platforms and msvc != '12'
is_protection_sdk_enabled = platform in protection_supported_platforms

file_target_name = 'mip_file_sdk'
protection_target_name = 'mip_protection_sdk'
upe_target_name = 'mip_upe_sdk'
wrappers = False
resources = []
samples_dir = '#'

env = Environment(**build_args)

env.Append(CXXFLAGS=Split(CXXFLAGS))
env.Append(LINKFLAGS=Split(LINKFLAGS))

if IsRHEL():
    env.Replace(CXX = "/opt/rh/devtoolset-7/root/usr/bin/c++")
    env.Replace(CC = "/opt/rh/devtoolset-7/root/usr/bin/gcc")
    env.Replace(CPP = "/opt/rh/devtoolset-7/root/usr/bin/cpp")

samples_path = env.GetLaunchDir()
#api_includes_dir = samples_path.replace('mipsdk-fileapi', 'include')
api_includes_dir = '/Users/abhijsri/Documents/mip-sdk-mac/mip_sdk_file_macos_1.1.217/include'
#bins = samples_path.replace('samples', 'bins' + '/' + build_flavor +'/' + target_arch)
#bins = '/Users/abhijsri/Documents/mip-sdk-mac/mip_sdk_file_macos_1.1.217/bins/debug/x86_64'
bins = '/Users/abhijsri/Documents/mip-sdk-mac/mipsdk-fileapi/bins'
#print "bins directory is equal to " + bins

Export("""
    api_includes_dir
    bins
    env
    file_target_name
    is_file_sdk_enabled
    is_protection_sdk_enabled
    platform
    protection_target_name
    resources
    samples_dir
    target_arch
    upe_target_name
    wrappers
""")

if platform == 'linux2':
    env.Append(CXXFLAGS=Split('-std=gnu++11 -D_REENTRANT'))

env.SConscript('SConscript', variant_dir=bins, duplicate=0)
#env.SConscript('SConscript', variant_dir=bins, src_dir='file', duplicate=0)