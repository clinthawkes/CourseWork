function toggleAddForm(check)
{
    // Toggle form on
    if (check == 1)
    {
        document.getElementById("add-fact-form").style.display="block";
        document.getElementById("add-fact-button").style.display="none";
    }
    else
    {
        document.getElementById("add-fact-form").style.display="none";
        document.getElementById("add-fact-button").style.display="inline";
    }
}