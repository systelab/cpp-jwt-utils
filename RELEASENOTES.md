# Summary of changes

## Changes for version 1.1.5 (25 Feb 2021)

### Bug Fixes

- Updated continuous integration to:
  - Use GitHub Action to generate library documentation
  - Upload generated packages to Systelab's public Artifactory


## Changes for version 1.1.4 (7 Sep 2020)

### Bug Fixes

- Moved RapidJSONAdapter dependency to version 1.1.0


## Changes for version 1.1.3 (31 Aug 2020)

### Bug Fixes

- Moved RapidJSONAdapter dependency to version 1.0.9


## Changes for version 1.1.2 (3 Jun 2020)

### Bug Fixes

- Moved RapidJSONAdapter dependency to version 1.0.8


## Changes for version 1.1.1 (2 Jun 2020)

### Bug Fixes

- Used gtest conan package from conan-center (without username/channel)


## Changes for version 1.1.0 (23 May 2020)

### Enhancements

- Added support for OpenSSL 1.1.1g


## Changes for version 1.0.8 (7 Apr 2020)

### Bug Fixes

- Moved RapidJSONAdapter dependency to version 1.0.7


## Changes for version 1.0.7 (7 Apr 2020)

### Bug Fixes

- Added abstract factory to build all library services
- Added mocks for auxiliary services


## Changes for version 1.0.6 (6 Feb 2020)

### Bug Fixes

- Fixed compilation for GoogleTest 1.10.0
- Fixed compilation for Visual Studio 2019


## Changes for version 1.0.5 (9 Dec 2019)

### Bug Fixes

- Moved RapidJSONAdapter dependency to version 1.0.5
- Updated Conan recipe to allow building from sources when missing required configuration
- Fixed Codacy issues


## Changes for version 1.0.4 (12 Nov 2019)

### Bug Fixes

- Moved RapidJSONAdapter dependency to version 1.0.4


## Changes for version 1.0.3 (10 Nov 2019)

### Bug Fixes

- Used latest version of RapidJSONAdapter dependency
- Added gtest as a build requirement when creating Conan package
- Created a separated package for test utilities


## Changes for version 1.0.2 (26 Sep 2019)

### Bug Fixes

- Add test utilities (mocks) for library services


## Changes for version 1.0.1 (3 Jul 2019)

### Bug Fixes

- Improved cmake and conan configuration to link only against used dependencies.


## Changes for version 1.0.0 (8 Apr 2019)

### Enhancements

- Initial version in GitHub (ported from internal SVN server)
