project(
    'bip39',
    'c',
    version : '0.2.1',
    default_options : ['warning_level=3']
)

project_source_files = [
    'src/bip39.c',
    'src/bip39.h',
    'src/bits.c',
    'src/bits.h',
    'src/main.c',
    'src/opts.c',
    'src/opts.h',
    'src/print.c',
    'src/print.h',
    'src/wordlist.c',
    'src/wordlist.h',
    'src/wordlists.c',
]

build_args = ['-Wno-overlength-strings']

project_dependencies = [ dependency('libsodium') ]

build_args += [
    '-DPROJECT_NAME="' + meson.project_name() + '"',
    '-DPROJECT_VERSION="' + meson.project_version() + '"',
]

project_target = executable(
    meson.project_name(),
    project_source_files,
    dependencies: project_dependencies,
    install : true,
    c_args : build_args,
)

tests_source_files = project_source_files + [
    'tests/bip39.h',
    'tests/bits.h',
    'tests/main.c',
    'tests/opts.h',
    'tests/wordlist.h',
]

tests_dependencies = project_dependencies + [ dependency('cunit') ]

tests_target = executable(
    'bip39_tests',
    tests_source_files,
    dependencies: tests_dependencies,
    c_args : build_args + ['-DCUNIT_TESTING'],
)

test('basic', tests_target)
