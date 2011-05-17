#!/usr/bin/ruby

PATH = "patchedXMLs/Savitri.xml"

File.open(PATH, "r") { |fp|

    inPara          = false     # we're currently scanning a line within a para
    firstLineOfPara = false     # we're at the head of a para
    versePara       = false     # the current para contains verse
    spacesBeforeSimpleList = ""

    fp.each { |line|
        if not inPara
            if line =~ /^\s*<para>\s*$/
                inPara = true
                firstLineOfPara = true
            end

            print line
        else
            if firstLineOfPara
                if line =~ /^(\s+).*<literallayout>$/
                    versePara = true
                    spacesBeforeSimpleList = Regexp.last_match[1]
                    print "#{spacesBeforeSimpleList}<simplelist>\n"
                else
                    versePara = false
                end
                firstLineOfPara = false
            end

            if versePara
                if line =~ /^\s*$/
                    print line
                    next
                end

                if line =~ /^\s*<\/para>/
                    inPara = false

                    print "#{spacesBeforeSimpleList}</simplelist>\n"
                    print line
                    next
                end

                if line =~ /^(\s+)(.*)<literallayout>$/
                    print "#{Regexp.last_match[1]}  <member>#{Regexp.last_match[2]}</member>\n"
                else
                    if (line !~ /^<\/literallayout>/ and line !~ /^\s*$/)
                        versePara = false
                        print "#{spacesBeforeSimpleList}</simplelist>\n"
                        print line
                    end
                end
            else
                if line =~ /^\s*<\/para>/
                    inPara = false
                end

                print line
            end
        end
    }
}
