local jsonFile = io.open("C:\\Users\\YOURNAME\\json.txt", "w")  -- Open a file to write JSON

if jsonFile then
    local list = getAddressList()  -- Get the list of addresses from Cheat Engine
    jsonFile:write('{"CheatTable":{"CheatEntries":{"CheatEntry":[')  -- Start of JSON structure

    for i = 0, list.Count-1 do
        local addressItem = list[i]  -- Get the address item at index i
        local address = tonumber(addressItem.Address, 16)  -- Convert the address to a number, assuming it's in hexadecimal
        if address then
            -- Format the address as JSON and write to file, add commas between entries
            jsonFile:write(string.format('{"Address":"%X"}', address))
            if i < list.Count - 1 then
                jsonFile:write(',')
            end
        else
            print("Error: Unable to convert address at index " .. i .. " to a number.")
        end
    end

    jsonFile:write(']}}}')  -- Close the JSON structure
    jsonFile:close()  -- Close the file
    print("Addresses have been saved in JSON format.")  -- Confirmation message
else
    print("Failed to open file for writing. - Made by Cjweb")  -- Error message in case file opening fails
end
