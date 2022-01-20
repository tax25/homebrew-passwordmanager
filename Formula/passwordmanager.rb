class Passwordmanager < Formula
  desc "Simple password manager written in C++"
  homepage "https://github.com/tax25/homebrew-passwordmanager"
  url "https://github.com/tax25/homebrew-passwordmanager/releases/download/v1.1.0/passwordmanager-mac.tar.gz"
  sha256 "bcb88169681052ffd66395b1267ddd09d105f4dcbd2a3f6762e5662ba7f4c992"
  version "1.1.0"

  def install
    bin.install "passwordmanager"
  end
end
