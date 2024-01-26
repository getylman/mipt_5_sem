USE bogomazovada;
SELECT TRANSFORM (ip, request_time, http_request, page_size, http_status, client_info)
USING 'sed "s/Safari/Chrome/"'
AS ip, request_time, http_request, page_size, http_status, client_info
FROM Logs 
LIMIT 10