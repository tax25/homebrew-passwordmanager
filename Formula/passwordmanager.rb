class Passwordmanager < Formula
  desc "Simple password manager written in C++"
  homepage "https://github.com/tax25/homebrew-passwordmanager"
  url "https://github.com/tax25/homebrew-passwordmanager/releases/download/Published/passwordmanager-mac.tar.gz"
  sha256 "0a21325384245bedad88f96be1962b269bce0cfd8920d7cf91e2f45598dc0df3"
  version "1.0.0"

  def install
    bin.install "passwordmanager"
  end
end
