# `actions/cache` Simple Test Project

This is a simple project, and a template project, using `actions/cache`.

The master branch provides only a CMake build system and a C program used as a unit test.

The build system checks if a test file with the right size and hash is available and, if not, downloads the file from a web site.

The unit test simply checks if it is possible to `fopen()` / `fclose()` the test file.

The goal of the test project is to implement a cache mechanism to avoid downloading the test file many times across multiple workflow runs. To do this, there are two branches/pull requests implementing different methods:

## branch `cache-test`, pull request #1 - pedrolcl/cachetest/pull/1

This method implements the cache using `actions/cache/save@v4` and `actions/cache/restore@v4`. The build system is responsible for downloading the test file when the cache does not exist.

## branch `alternative-cache`, pull request #2 - pedrolcl/cachetest/pull/2

This method uses `ethanjli/cached-download-action` to handle both downloading the test file and store/restore the cache. See https://github.com/ethanjli/cached-download-action.

## caveats

The `actions/cache` expect `zstd` to be available, which [is not true](https://github.com/actions/partner-runner-images/blob/main/images/arm-windows-11-image.md#omitted-software) in case the worklow runs on `windows-11-arm`. As a workaround, the Windows workflows implement this step:

```yml
    - name: 'Workaround for missing zstd in windows-11-arm'
      if: matrix.os == 'windows-11-arm'
      run: choco install zstandard
```

