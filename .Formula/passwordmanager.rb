class Passwordmanager < Formula
  desc "Simple password manager written in C++"
  homepage "https://github.com/tax25/homebrew-passwordmanager"
  url "https://github.com/tax25/homebrew-passwordmanager/releases/download/Published/passwordmanager-mac.tar.gz"
  sha256 "42138f7fe3d4a8f981c1fd8923f5cb6f4647cfd6390dfe373b492febf37e28c8"
  version "1.0.1"

  def install
    bin.install "passwordmanager"
  end
end
