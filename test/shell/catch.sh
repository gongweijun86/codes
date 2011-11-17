#!/bin/bash

content=`curl http://www.dianping.com/search/keyword/10/0_%E6%B8%B8%E6%B3%B3%E9%A6%86/" 
echo "get content:"
echo "----------------------------------"
#echo $content
echo "done"
echo "----------------------------------"

charset=`echo $content | sed "s/>/\n/g"`
echo $charset | grep "游泳馆"
