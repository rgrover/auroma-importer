#!/usr/bin/ruby

PATH = "parseableTexts/Savitri.txt.prenl"

File.open(PATH, "r") { |fp|
    started = false
    ended   = false
    fp.each { |line|
        if (not started)
            if line !~ /BOOK ONE: The Book of Beginnings/
                print line;
                next
            else
                started = true
            end
        end

        if not ended
            if line !~ /\\rl\{\\fsc THE END\}/
                if ((line !~ /^\s*$/)           and
                    (line !~ /^\\ht\s/)         and
                    (line !~ /^\\hn\s/)         and
                    (line !~ /^\\note\s/)       and
                    (line !~ /^Page\s(--|\d+)/) and
                    (line !~ /^\\par/)          and
                    (line !~ /^\\rl/)           and
                    (line !~ /^\\sect1/)        and
                    (line !~ /^\\sect2/))
                    line.chomp!
                    print "#{line}\\nl\n"
                    next
                end
            else
                ended = true
            end
        end

        print line
    }
}
