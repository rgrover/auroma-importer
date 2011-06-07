#!/usr/bin/ruby

# INPUT_FILE = "parseableTexts/Savitri.txt"
INPUT_FILE = "/tmp/Savitri.txt"

words = {}

fp = File.open(INPUT_FILE, "r")
fp.each {|line|
    line.chomp!
    line.split(/\s+|\x97/).each {|word|
        word.downcase!

        # strip trailing punctuation
        while word.sub!(/[,.;!?:'\x94\x97]$/, "") do
        end

        # remove odd things
        word.sub!(/'s$/, "")
        word.gsub!(/\\nl/,"")
        word.sub!(/^\(/, "")

        # skip unwanted words
        next if word.match(/^\d+/)
        next if word.match(/^\\/)
        next unless word.length > 0

        # add to hash
        if word.match(/\w$/)
            words[word] = 1
        end
    }
}

words.keys.sort.each {|word|
    puts word
}
