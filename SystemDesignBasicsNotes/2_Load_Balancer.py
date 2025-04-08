
# Load Balancer Algorithms:

### Round Robin: This is one of the simplest load balancing algorithms.
# It evenly distributes incoming requests to each server in a circular manner.
# When to use? It’s suitable for distributing traffic when all servers have similar
# capabilities and the workload is consistent.
# Limitation: However, it does not consider server load or response time, which can be inefficient
# when servers have varying capabilities.


### Least Connections: This algorithm directs incoming traffic to the server with the fewest
# active connections (maintained continuous connection) at the moment.
#
# Benefits: This method is effective when connections are relatively short-lived and server capacities differ.
# It optimizes resource usage by directing traffic to servers with the most available capacity.
# Gaming applications ->

# Limitations: One of the main limitations is that it assumes all requests are equal in terms of the resources
# required for processing. This assumption can lead to problems if a server receives a high number of
# resource-intensive requests.

### Least Bandwidth:
#
# Benefits: This method is suitable for applications where minimizing bandwidth usage is essential,
# such as media streaming platforms or download servers. It ensures efficient utilization of server
# resources.
# Limitations: The limitations of this method are not explicitly mentioned in the search results.
# However, one potential limitation could be that it might not perform well in scenarios where the
# size of the requests varies significantly.

### Least Response Time:
#
# Benefits: This method increases the availability time of servers.
# It assigns new requests evenly to each server to prevent overloading.
# Limitations: Since it is non-deterministic, the least response time load balancer
# is difficult to troubleshoot.

### Weighted Round Robin:
#
# Benefits: This method promotes efficient resource utilization by ensuring that all servers
# are used according to their capacity. It improves network performance by reducing the risk
# of server overload and provides fault tolerance by redirecting requests in case of server failure.
# Limitations: While Weighted Round Robin addresses the naivety of basic Round Robin,
# it adds complexity, requiring a method to assign and potentially update weights.
# Additionally, it still shares some limitations with its simpler counterpart,
# such as limited fault tolerance.

### IP Hash:
#
# Benefits: This method can provide an even spread of the traffic between the NICs in the team.
# It promotes fairness and efficiency in the distribution of network load, thereby reducing
# the risk of any single server becoming a bottleneck due to overload8.
# Limitations: One of the main disadvantages is the potential for uneven load distribution.
# If there is a significant disparity in the number of unique IP pairs, some servers may end
# up handling more requests than others. Hash collisions and redirection of loads are major
# limitations for recent Hash IP algorithms.


