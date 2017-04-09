import cgi, cgitb, webbrowser, urllib2
from subprocess import call

def transport():
    url = 'http://www.cs.mcgill.ca/~sli144/room.html'
    usrUrl = ''
    if url.endswith('room.html'):
        userUrl = url[:-9]
    resourcesLoc = 'http://cs.mcgill.ca/~mrunds/Game/resources.csv'
    roomLoc = 'http://cs.mcgill.ca/~mrunds/Game/room.html'
    try:
        input_file = open(resourcesLoc, "r")
        details = input_file.readlines()
        detailsLine1 = details[0]
        detailsLine1 = details.replace(" ", "")
        print detailsLine1
        resources = detailsLine1.split(',')
        occupiedOrNot = int (resources[2])
        print occupiedOrNot

        if occupiedOrNot == 1:
            call([userUrl + "room.cgi"])
            return

        else:
            output_file = open(resourcesLoc, "w")
            output_file.write(resources[0] + "," + resources[1] + "," + '0')
            html_file = urllib2.urlopen(roomLoc)
            print "Content-type: text/html"
            for line in html_file:
                line = line + ''
                if "inventory" not in line:
                    print line
                else:
                    mana = mana + ''
                    gold = gold + ''
                    print '<input type="hidden" name="inventory" value="%s,%s"></input>' %mana %gold
    
    except IOError:
        print 'Cannot open file'
        # call(["./room.cgi"])
    
    finally:
        input_file.close()
        output_file.close()