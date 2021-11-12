class Passwordmanager < Formula
  desc "Simple password manager written in C++"
  homepage "https://github.com/tax25/homebrew-passwordmanager"
  url "https://github.com/tax25/homebrew-passwordmanager/releases/download/v1.0.1/passwordmanager1_0_1-mac.tar.gz"
  sha256 "2d8ea3dc3a5f302a807e7f63351b74b296a420035890d3b165b0daaa4285fc72"
  version "1.0.1"

  def install
    bin.install "passwordmanager"
  end
end
