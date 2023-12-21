#ifndef _TQUIC_H_
#define _TQUIC_H_

/* Don't modify this file manually. It is autogenerated by cbindgen. */

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>

/**
 * The current QUIC wire version.
 */
#define QUIC_VERSION QUIC_VERSION_V1

/**
 * The QUIC Version 1
 */
#define QUIC_VERSION_V1 1

/**
 * Available congestion control algorithm
 */
typedef enum quic_congestion_control_algorithm {
  /**
   * CUBIC uses a cubic function instead of a linear window increase function
   * of the current TCP standards to improve scalability and stability under
   * fast and long-distance networks..
   */
  QUIC_CONGESTION_CONTROL_ALGORITHM_CUBIC,
  /**
   * BBR uses recent measurements of a transport connection's delivery rate,
   * round-trip time, and packet loss rate to build an explicit model of the
   * network path. The model is then used to control data transmission speed
   * and the maximum volume of data allowed in flight in the network at any
   * time.
   */
  QUIC_CONGESTION_CONTROL_ALGORITHM_BBR,
  /**
   * BBRv3 is the latest version of BBR, including various fixes and
   * algorithm updates that reduce packet re-transmit rate and slightly
   * improve latency. (Experimental)
   */
  QUIC_CONGESTION_CONTROL_ALGORITHM_BBR3,
  /**
   * COPA is a tunable delay-based congestion control algorithm. COPA is
   * based on an objective function where the trade-off between throughput
   * and delay can be configured via a user-specified parameter.
   * (Experimental)
   */
  QUIC_CONGESTION_CONTROL_ALGORITHM_COPA,
} quic_congestion_control_algorithm;

/**
 * The stream's side to shutdown.
 */
typedef enum quic_shutdown {
  /**
   * Stop receiving data on the stream.
   */
  QUIC_SHUTDOWN_READ = 0,
  /**
   * Stop sending data on the stream.
   */
  QUIC_SHUTDOWN_WRITE = 1,
} quic_shutdown;

/**
 * Configurations about QUIC endpoint.
 */
typedef struct quic_config_t quic_config_t;

/**
 * A QUIC connection.
 */
typedef struct quic_conn_t quic_conn_t;

/**
 * Endpoint is an entity that can participate in a QUIC connection by
 * generating, receiving, and processing QUIC packets.
 *
 * There are two types of endpoints in QUIC: client and server. Endpoint may
 * maintain one or more QUIC connections.  Endpoint provides a high level API
 * to use the QUIC library.
 */
typedef struct quic_endpoint_t quic_endpoint_t;

/**
 * An iterator over FourTuple.
 */
typedef struct quic_path_address_iter_t quic_path_address_iter_t;

/**
 * An HTTP/3 configuration.
 */
typedef struct http3_config_t http3_config_t;

/**
 * An HTTP/3 connection.
 */
typedef struct http3_conn_t http3_conn_t;

/**
 * An HTTP/3 header list.
 */
typedef struct http3_headers_t http3_headers_t;

typedef struct quic_tls_config_select_methods_t {
  SSL_CTX *(*get_default)(void *ctx);
  SSL_CTX *(*select)(void *ctx, const uint8_t *server_name, size_t server_name_len);
} quic_tls_config_select_methods_t;

typedef void *quic_tls_config_select_context_t;

typedef struct quic_transport_methods_t {
  /**
   * Called when a new connection has been created. This callback is called
   * as soon as connection object is created inside the endpoint, but
   * before the handshake is done. This callback is optional.
   */
  void (*on_conn_created)(void *tctx, struct quic_conn_t *conn);
  /**
   * Called when the handshake is completed. This callback is optional.
   */
  void (*on_conn_established)(void *tctx, struct quic_conn_t *conn);
  /**
   * Called when the connection is closed. The connection is no longer
   * accessible after this callback returns. It is a good time to clean up
   * the connection context. This callback is optional.
   */
  void (*on_conn_closed)(void *tctx, struct quic_conn_t *conn);
  /**
   * Called when the stream is created. This callback is optional.
   */
  void (*on_stream_created)(void *tctx, struct quic_conn_t *conn, uint64_t stream_id);
  /**
   * Called when the stream is readable. This callback is called when either
   * there are bytes to be read or an error is ready to be collected. This
   * callback is optional.
   */
  void (*on_stream_readable)(void *tctx, struct quic_conn_t *conn, uint64_t stream_id);
  /**
   * Called when the stream is writable. This callback is optional.
   */
  void (*on_stream_writable)(void *tctx, struct quic_conn_t *conn, uint64_t stream_id);
  /**
   * Called when the stream is closed. The stream is no longer accessible
   * after this callback returns. It is a good time to clean up the stream
   * context. This callback is optional.
   */
  void (*on_stream_closed)(void *tctx, struct quic_conn_t *conn, uint64_t stream_id);
  /**
   * Called when client receives a token in NEW_TOKEN frame. This callback
   * is optional.
   */
  void (*on_new_token)(void *tctx, struct quic_conn_t *conn, const uint8_t *token, size_t token_len);
} quic_transport_methods_t;

typedef void *quic_transport_context_t;

/**
 * Data and meta information of a outgoing packet.
 */
typedef struct quic_packet_out_spec_t {
  const struct iovec *iov;
  size_t iovlen;
  const void *src_addr;
  socklen_t src_addr_len;
  const void *dst_addr;
  socklen_t dst_addr_len;
} quic_packet_out_spec_t;

typedef struct quic_packet_send_methods_t {
  /**
   * Called when the connection is sending packets out.
   * On success, `on_packets_send()` returns the number of messages sent. If
   * this is less than count, the connection will retry with a further
   * `on_packets_send()` call to send the remaining messages. This callback
   * is mandatory.
   */
  int (*on_packets_send)(void *psctx, struct quic_packet_out_spec_t *pkts, unsigned int count);
} quic_packet_send_methods_t;

typedef void *quic_packet_send_context_t;

/**
 * Meta information of a incoming packet.
 */
typedef struct quic_packet_info_t {
  const struct sockaddr *src;
  socklen_t src_len;
  const struct sockaddr *dst;
  socklen_t dst_len;
} quic_packet_info_t;

typedef struct quic_path_address_t {
  struct sockaddr_storage local_addr;
  socklen_t local_addr_len;
  struct sockaddr_storage remote_addr;
  socklen_t remote_addr_len;
} quic_path_address_t;

typedef struct http3_methods_t {
  /**
   * Called when the stream got headers.
   */
  void (*on_stream_headers)(void *ctx,
                            uint64_t stream_id,
                            const struct http3_headers_t *headers,
                            bool fin);
  /**
   * Called when the stream has buffered data to read.
   */
  void (*on_stream_data)(void *ctx, uint64_t stream_id);
  /**
   * Called when the stream is finished.
   */
  void (*on_stream_finished)(void *ctx, uint64_t stream_id);
  /**
   * Called when the stream receives a RESET_STREAM frame from the peer.
   */
  void (*on_stream_reset)(void *ctx, uint64_t stream_id, uint64_t error_code);
  /**
   * Called when the stream priority is updated.
   */
  void (*on_stream_priority_update)(void *ctx, uint64_t stream_id);
  /**
   * Called when the connection receives a GOAWAY frame from the peer.
   */
  void (*on_conn_goaway)(void *ctx, uint64_t stream_id);
} http3_methods_t;

typedef void *http3_context_t;

/**
 * An extensible HTTP/3 Priority Parameters
 */
typedef struct http3_priority_t {
  uint8_t urgency;
  bool incremental;
} http3_priority_t;

typedef struct http3_header_t {
  uint8_t *name;
  uintptr_t name_len;
  uint8_t *value;
  uintptr_t value_len;
} http3_header_t;

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Check whether the protocol version is supported.
 */
bool quic_version_is_supported(uint32_t version);

/**
 * Create default configuration.
 * The caller is responsible for the memory of the Config and should properly
 * destroy it by calling `quic_config_free`.
 */
struct quic_config_t *quic_config_new(void);

/**
 * Destroy a Config instance.
 */
void quic_config_free(struct quic_config_t *config);

/**
 * Set the `max_idle_timeout` transport parameter in milliseconds.
 */
void quic_config_set_max_idle_timeout(struct quic_config_t *config, uint64_t v);

/**
 * Set handshake timeout in milliseconds. Zero turns the timeout off.
 */
void quic_config_set_max_handshake_timeout(struct quic_config_t *config, uint64_t v);

/**
 * Set the `max_udp_payload_size` transport parameter in bytes. It limits
 * the size of UDP payloads that the endpoint is willing to receive.
 */
void quic_config_set_recv_udp_payload_size(struct quic_config_t *config, uint16_t v);

/**
 * Set the maximum outgoing UDP payload size.
 * This is depended on both the configured max payload size and the max_udp_payload_size
 * transport parameter advertised by the remote peer.
 * The default and minimum value is `1200`.
 */
void quic_config_set_send_udp_payload_size(struct quic_config_t *config, uintptr_t v);

/**
 * Set the `initial_max_data` transport parameter. It means the initial
 * value for the maximum amount of data that can be sent on the connection.
 */
void quic_config_set_initial_max_data(struct quic_config_t *config, uint64_t v);

/**
 * Set the `initial_max_stream_data_bidi_local` transport parameter.
 */
void quic_config_set_initial_max_stream_data_bidi_local(struct quic_config_t *config, uint64_t v);

/**
 * Set the `initial_max_stream_data_bidi_remote` transport parameter.
 */
void quic_config_set_initial_max_stream_data_bidi_remote(struct quic_config_t *config, uint64_t v);

/**
 * Set the `initial_max_stream_data_uni` transport parameter.
 */
void quic_config_set_initial_max_stream_data_uni(struct quic_config_t *config, uint64_t v);

/**
 * Set the `initial_max_streams_bidi` transport parameter.
 */
void quic_config_set_initial_max_streams_bidi(struct quic_config_t *config, uint64_t v);

/**
 * Set the `initial_max_streams_uni` transport parameter.
 */
void quic_config_set_initial_max_streams_uni(struct quic_config_t *config, uint64_t v);

/**
 * Set the `ack_delay_exponent` transport parameter.
 */
void quic_config_set_ack_delay_exponent(struct quic_config_t *config, uint64_t v);

/**
 * Set the `max_ack_delay` transport parameter.
 */
void quic_config_set_max_ack_delay(struct quic_config_t *config, uint64_t v);

/**
 * Set congestion control algorithm that the connection would use.
 */
void quic_config_set_congestion_control_algorithm(struct quic_config_t *config,
                                                  enum quic_congestion_control_algorithm v);

/**
 * Set the initial congestion window in packets.
 * The default value is 10.
 */
void quic_config_set_initial_congestion_window(struct quic_config_t *config, uint64_t v);

/**
 * Set the minimal congestion window in packets.
 * The default value is 2.
 */
void quic_config_set_min_congestion_window(struct quic_config_t *config, uint64_t v);

/**
 * Set the initial RTT in milliseconds. The default value is 333ms.
 * The configuration should be changed with caution. Setting a value less than the default
 * will cause retransmission of handshake packets to be more aggressive.
 */
void quic_config_set_initial_rtt(struct quic_config_t *config, uint64_t v);

/**
 * Set the `active_connection_id_limit` transport parameter.
 */
void quic_config_set_active_connection_id_limit(struct quic_config_t *config, uint64_t v);

/**
 * Set the maximum size of the connection flow control window.
 */
void quic_config_set_max_connection_window(struct quic_config_t *config, uint64_t v);

/**
 * Set the maximum size of the stream flow control window.
 */
void quic_config_set_max_stream_window(struct quic_config_t *config, uint64_t v);

/**
 * Set the Maximum number of concurrent connections.
 */
void quic_config_set_max_concurrent_conns(struct quic_config_t *config, uint32_t v);

/**
 * Set the key for reset token generation. The token_key_len should be not less
 * than 64.
 */
int quic_config_set_reset_token_key(struct quic_config_t *config,
                                    const uint8_t *token_key,
                                    size_t token_key_len);

/**
 * Set whether stateless reset is allowed.
 */
void quic_config_enable_stateless_reset(struct quic_config_t *config, bool enabled);

/**
 * Set the lifetime of address token.
 */
void quic_config_set_address_token_lifetime(struct quic_config_t *config, uint64_t seconds);

/**
 * Set the key for address token generation.
 * The token_key_len should be a multiple of 16.
 */
int quic_config_set_address_token_key(struct quic_config_t *config,
                                      const uint8_t *token_keys,
                                      size_t token_keys_len);

/**
 * Set whether stateless retry is allowed. Default is not allowed.
 */
void quic_config_enable_retry(struct quic_config_t *config, bool enabled);

/**
 * Set the length of source cid. The length should not be greater than 20.
 */
void quic_config_set_cid_len(struct quic_config_t *config, uint8_t v);

/**
 * Set the batch size for sending packets.
 */
void quic_config_set_send_batch_size(struct quic_config_t *config, uint16_t v);

/**
 * Set TLS config selector.
 */
void quic_config_set_tls_selector(struct quic_config_t *config,
                                  const struct quic_tls_config_select_methods_t *methods,
                                  quic_tls_config_select_context_t context);

/**
 * Set TLS config.
 * The caller is responsible for the memory of SSL_CTX when use this function.
 */
void quic_config_set_tls_config(struct quic_config_t *config, SSL_CTX *ssl_ctx);

/**
 * Create a QUIC endpoint.
 *
 * The caller is responsible for the memory of the Endpoint and properly
 * destroy it by calling `quic_endpoint_free`.
 *
 * Note: The endpoint doesn't own the underlying resources provided by the C
 * caller. It is the responsibility of the caller to ensure that these
 * resources outlive the endpoint and release them correctly.
 */
struct quic_endpoint_t *quic_endpoint_new(struct quic_config_t *config,
                                          bool is_server,
                                          const struct quic_transport_methods_t *handler_methods,
                                          quic_transport_context_t handler_ctx,
                                          const struct quic_packet_send_methods_t *sender_methods,
                                          quic_packet_send_context_t sender_ctx);

/**
 * Destroy a QUIC endpoint.
 */
void quic_endpoint_free(struct quic_endpoint_t *endpoint);

/**
 * Create a client connection.
 * If success, the output parameter `index` carrys the index of the connection.
 */
int quic_endpoint_connect(struct quic_endpoint_t *endpoint,
                          const struct sockaddr *local,
                          socklen_t local_len,
                          const struct sockaddr *remote,
                          socklen_t remote_len,
                          const char *server_name,
                          const uint8_t *session,
                          size_t session_len,
                          const uint8_t *token,
                          size_t token_len,
                          uint64_t *index);

/**
 * Process an incoming UDP datagram.
 */
int quic_endpoint_recv(struct quic_endpoint_t *endpoint,
                       uint8_t *buf,
                       size_t buf_len,
                       const struct quic_packet_info_t *info);

/**
 * Return the amount of time until the next timeout event.
 */
uint64_t quic_endpoint_timeout(const struct quic_endpoint_t *endpoint);

/**
 * Process timeout events on the endpoint.
 */
void quic_endpoint_on_timeout(struct quic_endpoint_t *endpoint);

/**
 * Process internal events of all tickable connections.
 */
int quic_endpoint_process_connections(struct quic_endpoint_t *endpoint);

/**
 * Check whether the given connection exists.
 */
bool quic_endpoint_exist_connection(struct quic_endpoint_t *endpoint,
                                    const uint8_t *cid,
                                    size_t cid_len);

/**
 * Get the connection by index
 */
struct quic_conn_t *quic_endpoint_get_connection(struct quic_endpoint_t *endpoint, uint64_t index);

/**
 * Gracefully or forcibly shutdown the endpoint.
 * If `force` is false, cease creating new connections and wait for all
 * active connections to close. Otherwise, forcibly close all the active
 * connections.
 */
void quic_endpoint_close(struct quic_endpoint_t *endpoint, bool force);

/**
 * Get index of the connection
 */
uint64_t quic_conn_index(struct quic_conn_t *conn);

/**
 * Check whether the connection is a server connection.
 */
bool quic_conn_is_server(struct quic_conn_t *conn);

/**
 * Check whether the connection handshake is complete.
 */
bool quic_conn_is_established(struct quic_conn_t *conn);

/**
 * Check whether the connection is created by a resumed handshake.
 */
bool quic_conn_is_resumed(struct quic_conn_t *conn);

/**
 * Check whether the connection has a pending handshake that has progressed
 * enough to send or receive early data.
 */
bool quic_conn_is_in_early_data(struct quic_conn_t *conn);

/**
 * Check whether the established connection works in multipath mode.
 */
bool quic_conn_is_multipath(struct quic_conn_t *conn);

/**
 * Return the negotiated application level protocol.
 */
void quic_conn_application_proto(struct quic_conn_t *conn, const uint8_t **out, size_t *out_len);

/**
 * Return the server name in the TLS SNI extension.
 */
void quic_conn_server_name(struct quic_conn_t *conn, const uint8_t **out, size_t *out_len);

/**
 * Return the session data used by resumption.
 */
void quic_conn_session(struct quic_conn_t *conn, const uint8_t **out, size_t *out_len);

/**
 * Add a new path on the client connection.
 */
int quic_conn_add_path(struct quic_conn_t *conn,
                       const struct sockaddr *local,
                       socklen_t local_len,
                       const struct sockaddr *remote,
                       socklen_t remote_len,
                       uint64_t *index);

/**
 * Remove a path on the client connection.
 */
int quic_conn_abandon_path(struct quic_conn_t *conn,
                           const struct sockaddr *local,
                           socklen_t local_len,
                           const struct sockaddr *remote,
                           socklen_t remote_len);

/**
 * Migrate the client connection to the specified path.
 */
int quic_conn_migrate_path(struct quic_conn_t *conn,
                           const struct sockaddr *local,
                           socklen_t local_len,
                           const struct sockaddr *remote,
                           socklen_t remote_len);

/**
 * Return an iterator over path addresses.
 * The caller should properly destroy it by calling `quic_four_tuple_iter_free`.
 */
struct quic_path_address_iter_t *quic_conn_paths(struct quic_conn_t *conn);

/**
 * Destroy the FourTupleIter
 */
void quic_conn_path_iter_free(struct quic_path_address_iter_t *iter);

/**
 * Return the address of the next path.
 */
bool quic_conn_path_iter_next(struct quic_path_address_iter_t *iter, struct quic_path_address_t *a);

/**
 * Return the address of the active path
 */
bool quic_conn_active_path(const struct quic_conn_t *conn, struct quic_path_address_t *a);

/**
 * Return the trace id of the connection
 */
void quic_conn_trace_id(struct quic_conn_t *conn, const uint8_t **out, size_t *out_len);

/**
 * Check whether the connection is draining.
 */
bool quic_conn_is_draining(struct quic_conn_t *conn);

/**
 * Check whether the connection is closing.
 */
bool quic_conn_is_closed(struct quic_conn_t *conn);

/**
 * Check whether the connection was closed due to idle timeout.
 */
bool quic_conn_is_idle_timeout(struct quic_conn_t *conn);

/**
 * Returns the error from the peer, if any.
 */
bool quic_conn_peer_error(struct quic_conn_t *conn,
                          bool *is_app,
                          uint64_t *error_code,
                          const uint8_t **reason,
                          size_t *reason_len);

/**
 * Returns the local error, if any.
 */
bool quic_conn_local_error(struct quic_conn_t *conn,
                           bool *is_app,
                           uint64_t *error_code,
                           const uint8_t **reason,
                           size_t *reason_len);

/**
 * Set user context for the connection.
 */
void quic_conn_set_context(struct quic_conn_t *conn, void *data);

/**
 * Get user context for the connection.
 */
void *quic_conn_context(struct quic_conn_t *conn);

/**
 * Set keylog file
 */
void quic_conn_set_keylog_fd(struct quic_conn_t *conn, int fd);

/**
 * Set qlog file
 */
void quic_conn_set_qlog_fd(struct quic_conn_t *conn, int fd, const char *title, const char *desc);

/**
 * Close the connection.
 */
int quic_conn_close(struct quic_conn_t *conn,
                    bool app,
                    uint64_t err,
                    const uint8_t *reason,
                    size_t reason_len);

/**
 * Set want write flag for a stream.
 */
int quic_stream_wantwrite(struct quic_conn_t *conn, uint64_t stream_id, bool want);

/**
 * Set want read flag for a stream.
 */
int quic_stream_wantread(struct quic_conn_t *conn, uint64_t stream_id, bool want);

/**
 * Read data from a stream.
 */
ssize_t quic_stream_read(struct quic_conn_t *conn,
                         uint64_t stream_id,
                         uint8_t *out,
                         size_t out_len,
                         bool *fin);

/**
 * Write data to a stream.
 */
ssize_t quic_stream_write(struct quic_conn_t *conn,
                          uint64_t stream_id,
                          const uint8_t *buf,
                          size_t buf_len,
                          bool fin);

/**
 * Create a new quic transport stream with the given id and priority.
 */
int quic_stream_new(struct quic_conn_t *conn,
                    uint64_t stream_id,
                    uint8_t urgency,
                    bool incremental);

/**
 * Shutdown stream reading or writing.
 */
int quic_stream_shutdown(struct quic_conn_t *conn,
                         uint64_t stream_id,
                         enum quic_shutdown direction,
                         uint64_t err);

/**
 * Set the priority for a stream.
 */
int quic_stream_set_priority(struct quic_conn_t *conn,
                             uint64_t stream_id,
                             uint8_t urgency,
                             bool incremental);

/**
 * Return the stream’s send capacity in bytes.
 */
ssize_t quic_stream_capacity(struct quic_conn_t *conn, uint64_t stream_id);

/**
 * Return true if all the data has been read from the stream.
 */
bool quic_stream_finished(struct quic_conn_t *conn, uint64_t stream_id);

/**
 * Set user context for a stream.
 */
int quic_stream_set_context(struct quic_conn_t *conn, uint64_t stream_id, void *data);

/**
 * Return the stream’s user context.
 */
void *quic_stream_context(struct quic_conn_t *conn, uint64_t stream_id);

/**
 * Create default config for HTTP3.
 */
struct http3_config_t *http3_config_new(void);

/**
 * Destroy the HTTP3 config.
 */
void http3_config_free(struct http3_config_t *config);

/**
 * Set the `SETTINGS_MAX_FIELD_SECTION_SIZE` setting.
 * By default no limit is enforced.
 */
void http3_config_set_max_field_section_size(struct http3_config_t *config, uint64_t v);

/**
 * Set the `SETTINGS_QPACK_MAX_TABLE_CAPACITY` setting.
 * The default value is `0`.
 */
void http3_config_set_qpack_max_table_capacity(struct http3_config_t *config, uint64_t v);

/**
 * Set the `SETTINGS_QPACK_BLOCKED_STREAMS` setting.
 * The default value is `0`.
 */
void http3_config_set_qpack_blocked_streams(struct http3_config_t *config, uint64_t v);

/**
 * Create an HTTP/3 connection using the given QUIC connection. It also
 * initiate the HTTP/3 handshake by opening all control streams and sending
 * the local settings.
 */
struct http3_conn_t *http3_conn_new(struct quic_conn_t *quic_conn, struct http3_config_t *config);

/**
 * Destroy the HTTP/3 connection.
 */
void http3_conn_free(struct http3_conn_t *conn);

/**
 * Send goaway with the given id.
 */
int64_t http3_send_goaway(struct http3_conn_t *conn, struct quic_conn_t *quic_conn, uint64_t id);

/**
 * Set HTTP/3 connection events handler.
 */
void http3_conn_set_events_handler(struct http3_conn_t *conn,
                                   const struct http3_methods_t *methods,
                                   http3_context_t context);

/**
 * Process HTTP/3 settings.
 */
int http3_for_each_setting(const struct http3_conn_t *conn, int (*cb)(uint64_t identifier,
                                                                      uint64_t value,
                                                                      void *argp), void *argp);

/**
 * Process internal events of all streams of the specified HTTP/3 connection.
 */
int http3_conn_process_streams(struct http3_conn_t *conn, struct quic_conn_t *quic_conn);

/**
 * Process HTTP/3 headers.
 */
int http3_for_each_header(const struct http3_headers_t *headers, int (*cb)(const uint8_t *name,
                                                                           size_t name_len,
                                                                           const uint8_t *value,
                                                                           size_t value_len,
                                                                           void *argp), void *argp);

/**
 * Return true if all the data has been read from the stream.
 */
bool http3_stream_read_finished(struct quic_conn_t *conn, uint64_t stream_id);

/**
 * Create a new HTTP/3 request stream.
 * On success the stream ID is returned.
 */
int64_t http3_stream_new(struct http3_conn_t *conn, struct quic_conn_t *quic_conn);

/**
 * Create a new HTTP/3 request stream with the given priority.
 * On success the stream ID is returned.
 */
int64_t http3_stream_new_with_priority(struct http3_conn_t *conn,
                                       struct quic_conn_t *quic_conn,
                                       const struct http3_priority_t *priority);

/**
 * Set priority for an HTTP/3 stream.
 */
int http3_stream_set_priority(struct http3_conn_t *conn,
                              struct quic_conn_t *quic_conn,
                              uint64_t stream_id,
                              const struct http3_priority_t *priority);

/**
 * Close the given HTTP/3 stream.
 */
int http3_stream_close(struct http3_conn_t *conn,
                       struct quic_conn_t *quic_conn,
                       uint64_t stream_id);

/**
 * Send HTTP/3 request or response headers on the given stream.
 */
int http3_send_headers(struct http3_conn_t *conn,
                       struct quic_conn_t *quic_conn,
                       uint64_t stream_id,
                       const struct http3_header_t *headers,
                       size_t headers_len,
                       bool fin);

/**
 * Send HTTP/3 request or response body on the given stream.
 */
ssize_t http3_send_body(struct http3_conn_t *conn,
                        struct quic_conn_t *quic_conn,
                        uint64_t stream_id,
                        const uint8_t *body,
                        size_t body_len,
                        bool fin);

/**
 * Read request/response body from the given stream.
 */
ssize_t http3_recv_body(struct http3_conn_t *conn,
                        struct quic_conn_t *quic_conn,
                        uint64_t stream_id,
                        uint8_t *out,
                        size_t out_len);

/**
 * Parse HTTP/3 priority data.
 */
int http3_parse_extensible_priority(const uint8_t *priority,
                                    size_t priority_len,
                                    struct http3_priority_t *parsed);

/**
 * Send a PRIORITY_UPDATE frame on the control stream with specified
 * request stream ID and priority.
 */
int http3_send_priority_update_for_request(struct http3_conn_t *conn,
                                           struct quic_conn_t *quic_conn,
                                           uint64_t stream_id,
                                           const struct http3_priority_t *priority);

/**
 * Take the last PRIORITY_UPDATE for the given stream.
 */
int http3_take_priority_update(struct http3_conn_t *conn,
                               uint64_t prioritized_element_id,
                               int (*cb)(const uint8_t *priority_field_value,
                                         size_t priority_field_value_len,
                                         void *argp),
                               void *argp);

/**
 * An enum representing the available verbosity level filters of the logger.
 */
typedef enum quic_log_level {
  /**
   * A level lower than all log levels.
   */
  QUIC_LOG_LEVEL_OFF,
  /**
   * Corresponds to the `Error` log level.
   */
  QUIC_LOG_LEVEL_ERROR,
  /**
   * Corresponds to the `Warn` log level.
   */
  QUIC_LOG_LEVEL_WARN,
  /**
   * Corresponds to the `Info` log level.
   */
  QUIC_LOG_LEVEL_INFO,
  /**
   * Corresponds to the `Debug` log level.
   */
  QUIC_LOG_LEVEL_DEBUG,
  /**
   * Corresponds to the `Trace` log level.
   */
  QUIC_LOG_LEVEL_TRACE,
} quic_log_level;

/**
 * Set logger.
 * `cb` is a callback function that will be called for each log message.
 * `line` is a null-terminated log message and `argp` is user-defined data that will be passed to
 * the callback.
 * `level` represents the log level.
 */
void quic_set_logger(void (*cb)(const uint8_t *line, void *argp), void *argp, quic_log_level level);

typedef enum http3_error {
    HTTP3_NO_ERROR = 0,

    // There is no error or no work to do
    HTTP3_ERR_DONE = -1,

    // The endpoint detected an error in the protocol
    HTTP3_ERR_GENERAL_PROTOCOL_ERROR = -2,

    // The endpoint encountered an internal error and cannot continue with the
    // connection
    HTTP3_ERR_INTERNAL_ERROR = -3,

    // The endpoint detected that its peer created a stream that it will not
    // accept
    HTTP3_ERR_STREAM_CREATION_ERROR = -4,

    // A stream required by the connection was closed or reset
    HTTP3_ERR_CLOSED_CRITICAL_STREAM = -5,

    // A frame was received which is not permitted in the current state or on
    // the current stream
    HTTP3_ERR_FRAME_UNEXPECTED = -6,

    // A frame that fails to satisfy layout requirements or with an invalid
    // size was received
    HTTP3_ERR_FRAME_ERROR = -7,

    // The endpoint detected that its peer is exhibiting a behavior that might
    // be generating excessive load
    HTTP3_ERR_EXCESSIVE_LOAD = -8,

    // A stream ID or push ID was used incorrectly, such as exceeding a limit,
    // reducing a limit, or being reused
    HTTP3_ERR_ID_ERROR = -9,

    // An endpoint detected an error in the payload of a SETTINGS frame
    HTTP3_ERR_SETTINGS_ERROR = -10,

    // No SETTINGS frame was received at the beginning of the control stream
    HTTP3_ERR_MISSING_SETTINGS = -11,

    // -12 reserved

    // The stream is blocked
    HTTP3_ERR_STREAM_BLOCKED = -13,

    // The server rejected the request without performing any application
    // processing
    HTTP3_ERR_REQUEST_REJECTED = -14,

    // The request or its response (including pushed response) is cancelled
    HTTP3_ERR_REQUEST_CANCELLED = -15,

    // The client's stream terminated without containing a fully-formed request
    HTTP3_ERR_REQUEST_INCOMPLETE = -16,

    // An HTTP message was malformed and cannot be processed
    HTTP3_ERR_MESSAGE_ERROR = -17,

    // The TCP connection established in response to a CONNECT request was
    // reset or abnormally closed
    HTTP3_ERR_CONNECT_ERROR = -18,

    // The requested operation cannot be served over HTTP/3. The peer should
    // retry over HTTP/1.1
    HTTP3_ERR_VERSION_FALLBACK = -19,

    // The decoder failed to interpret an encoded field section and is not
    // able to continue decoding that field section
    HTTP3_ERR_QPACK_DECOMPRESSION_FAILED = -20,

    // The decoder failed to interpret an encoder instruction received on the
    // encoder stream
    HTTP3_ERR_QPACK_ENCODER_STREAM_ERROR = -21,

    // The encoder failed to interpret a decoder instruction received on the
    // decoder stream
    HTTP3_ERR_QPACK_DECODER_STREAM_ERROR = -22,
} http3_error;

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* _TQUIC_H_ */
