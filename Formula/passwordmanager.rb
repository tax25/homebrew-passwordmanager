class Passwordmanager < Formula
  desc "Simple password manager written in C++"
  homepage "https://github.com/tax25/homebrew-passwordmanager"
  url "https://github.com/tax25/homebrew-passwordmanager/releases/download/v1.1.1/pwdManager-mac.tar.gz"
  sha256 "8085890cf55de8f7ec7a11cd1227415d014cf13e6ae0a344679e568a113f7b9f"
  version "1.1.1"

  def install
    bin.install "pwdManager"
  end
end
