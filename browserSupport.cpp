/*
 * browserSupport.cpp
 *
 *  Created on: Apr 20, 2019
 *      Author: dgv130030
 */

#include "browserSupport.h"

#include <string>


url::operator std::string() const
{
    return text();
}

std::vector<url> *browserSupport::pVector = nullptr;

url:: url()
:    urlText(), urlValid(false)
{
    
}

url:: url(const std::string &urlText)
{
    this->urlText = urlText;
    urlValid = true;
}

url:: ~url()
{
}

void url:: text(const std::string &urlText)
{
    this->urlText =urlText;
}

std::string url:: text() const
{
    return urlText;
}
bool url:: valid() const
{
    return urlValid;
}
bool url :: operator< (const url& rhs) const
{
    return urlText<rhs.urlText;
}
bool url:: operator==(const url& rhs) const
{
    return urlText == rhs.urlText;
}


std::ostream& operator<<(std::ostream &out, const url &other)
{
    out<< other.text()<<std::endl;
    return out;
}





browserSupport:: browserSupport()
: historyQueue(), oldObjBack(), oldObjFront(), max(50), currentUrl()
{
    
}

browserSupport::~browserSupport()
{
}


url browserSupport:: back()
{
    if(!oldObjBack.empty())
    {
        if(currentUrl.valid())
        {
            oldObjFront.push(currentUrl);
        }
        currentUrl = oldObjBack.top();
        oldObjBack.pop();
    }
    return currentUrl;
}

url browserSupport:: forward()
{
    if(!oldObjFront.empty())
    {
        if(currentUrl.valid())
        {
            oldObjBack.push(currentUrl);
        }
        currentUrl = oldObjFront.top();
        oldObjFront.pop();
    }
    return currentUrl;
}

void browserSupport:: display(const url &newURL)
{
    if(currentUrl.valid())
    {
        oldObjBack.push(currentUrl);
    }
    
    if(newURL.valid())
    {
        currentUrl = newURL;
        if(!historyQueue.empty())
        {
            if(historyQueue.back() != currentUrl)
            {
                historyQueue.push(currentUrl);
            
                while (historyQueue.size() > max)
                {
                    historyQueue.pop();
                }
            }
        }
        else
        {
            historyQueue.push(newURL);
        }
        oldObjFront.clear();
    }
}

std::size_t browserSupport:: clearHistory()
{
    std::size_t size = historyQueue.size();
    historyQueue.clear();
    return size;
}
std::size_t browserSupport:: clearCache()
{
    //need to set current url back to default
    std::size_t returnSize = 0;
    if(currentUrl.valid())
    {
        returnSize++;
    }
    returnSize += oldObjFront.size();
    returnSize += oldObjBack.size();
    oldObjBack.clear();
    oldObjFront.clear();
    return returnSize;
}

std::size_t browserSupport :: maximum() const
{
    return max;
}

void browserSupport :: maximum(std::size_t newMax)
{
    max = newMax;
    while (historyQueue.size() > max)
    {
        historyQueue.pop();
    }
}


void browserSupport::buildHistory(const url &nextURL)
{
	//if (pVector != nullptr)
	
		(*pVector).push_back(nextURL);
	
}

std::size_t browserSupport::history(std::vector<url> &historyURLs)
{
	historyURLs.clear();
	browserSupport::pVector = &historyURLs;

	historyQueue.traverse(&browserSupport::buildHistory);


	//browserSupport::pVector = nullptr;

	return 0;
}
