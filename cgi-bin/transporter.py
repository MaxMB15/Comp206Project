import cgi, cgitb, webbrowser, urllib2

def transport():
    """form = cgi.FieldStorage()
    inventoryVals = form.getvalue('inventory')
    inventoryAsList = inventoryVals.split(',')
    mana = int (inventoryAsList[0])
    if mana == 0:
        print "Content-type: text/html"
        print
        print "<html><head>"
        print "<>"
        return """
    url = 'http://www.cs.mcgill.ca/~sli144/room.html'
    if url.endswith('room.html'):
        url = url[:-9]
    resourcesLoc = url + "cgi-bin/resources.csv"
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
            webbrowser.open_new(url)
    
    except IOError:
        print 'Cannot open file'
transport()
