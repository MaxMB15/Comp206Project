import cgi, cgitb, webbrowser, urllib2

def transport():
    """form = cgi.FieldStorage()
    inventoryVals = form.getvalue('inventory')
    # print inventoryVals
    # inventoryAsList = inventoryVals.split(',')
    mana = inventoryVals[0]
    gold = inventoryVals[1]
    mana = int (inventoryAsList[0])
    gold = int (inventoryAsList[1])
    if mana == 0:
        print "Content-type: text/html"
        print
        print "<html><head>"
        print "<>"
        return """
    url = 'http://www.cs.mcgill.ca/~sli144/room.html'
    if url.endswith('room.html'):
        userUrl = url[:-9]
    resourcesLoc = userUrl + "cgi-bin/resources.csv"
    # resourcesLoc = "resources.csv"
    try:
        # input_file = open(resourcesLoc, "r")
        input_file = urllib2.urlopen(resourcesLoc)
        details = input_file.readlines()
        details = details[0]
        details = details.replace(" ", "")
        print details
        occupiedOrNot = details.split(',')
        occupiedOrNot = int (occupiedOrNot[2])
        print occupiedOrNot

        if occupiedOrNot == 1:
            print 'Occupied room!'
            return
        else:
            print 'Unoccupied room! We can go in!'
            html_file = urllib2.urlopen(url)
            print "Content-type: text/html"
            for line in html_file:
                line = line + ''
                if "inventory" not in line:
                    print line
                else:
                    mana = mana + ''
                    gold = gold + ''
                    print '<input type="hidden" name="inventory" value="%s,%s">' %mana %gold
            
            # webbrowser.open_new(url)
    
    except IOError:
        print 'Cannot open file'
transport()
