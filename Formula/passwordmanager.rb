class Passwordmanager < Formula
  desc "Simple password manager written in C++"
  homepage "https://github.com/tax25/homebrew-passwordmanager"
  url "https://github.com/tax25/homebrew-passwordmanager/releases/download/v1.1.0/passwordmanager-mac.tar.gz"
  sha256 "1a6f5ea7dcc21d074b0ffaca34cc5dbfd126dba567398bd282aaf45e8d5d2d3d"
  version "1.1.0"

  def install
    bin.install "passwordmanager"
  end
end
