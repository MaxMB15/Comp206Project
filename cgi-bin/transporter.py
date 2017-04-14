import cgi, cgitb, urllib2
from subprocess import call

def transport():
    """ From the form on the web page,
        we get the player's inventory
        and the url of the room that
        they came from """
    form = cgi.FieldStorage()
    inventoryVals = form.getvalue('inventory')
    url = form.getvalue('url')
    # url = 'http://www.cs.mcgill.ca/~sli144/room.html'
    inventoryVals = inventoryVals + ''
    inventoryAsList = inventoryVals.split(',')
    mana = inventoryAsList[0]
    gold = inventoryAsList[1]

    usrUrl = ''
    if url.endswith('room.html'):
        userUrl = url[:-9]
    
    """ resources.csv is stored in the
        same place as transporter.py and
        room.html is stored one level above """
    resourcesLoc = './resources.csv'
    roomLoc = '../room.html'

    try:
        """ we access the resources file and
            get the last number which tells us
            if the room is occupied or not """
        input_file = open(resourcesLoc, "r")
        details = input_file.readlines()
        detailsLine1 = details[0]
        detailsLine1 = detailsLine1.replace(" ", "")
        # print detailsLine1
        resources = detailsLine1.split(',')
        occupiedOrNot = int (resources[2])
        # print occupiedOrNot

        """ if the room is occupied we send
            the player back to the room where
            they came from by calling the program
            on the previous website """
        if occupiedOrNot == 1:
            call([userUrl + "room.cgi"])
            return

        else:
            """ if the room is not occupied, we
                change our resources to reflect
                that it is now occupied and we
                print out the webpage """
            output_file = open(resourcesLoc, "w")
            output_file.write(resources[0] + "," + resources[1] + "," + '1')
            html_file = open(roomLoc, "r")
            print "Content-type:text/html\n\n"
            for line in html_file:
                line = line + ''
                if "inventory" not in line:
                    print line
                else:
                    print '<input type="hidden" name="inventory" value="%s,%s"></input>' %mana %gold
    
    except IOError:
        print "Cannot open file"

    finally:
        input_file.close()
        output_file.close()
        html_file.close()
    

transport()