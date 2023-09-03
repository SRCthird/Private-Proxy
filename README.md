# MS Edge Private Proxy

A C++ application that proxies URLs to an in-private MS Edge session.

## Potential usage

This can be used to redirect shared account to login pages of web applications that require authentication. Some web applications may require authentication upon loading, so if a user were to be logged in under an account that doesn't have access to that application, this Private Proxy can be used to redirect from a 3rd party application.

Like creating a Microsoft PowerApp that sends the user to `127.0.0.1/?url=company.website.com`.

## Prerequisites

- Microsoft Edge browser installed

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/SRCthird/Private-Proxy.git
   ```

2. Navigate to the project directory:

   ```bash
   cd Private-Proxy
   ```

## Configuration

You can adjust server settings by editing the `config.json` file:

```json
{
  "on-start": true,
  "port": 42310
}
```

- `on-start`: Whether the application should start on startup. Default is true.
- `port`: The port on which the server will run.Default is 42830.

## Usage

### Start the program:
```bash
private-proxy --start
```

### Send a `GET` request to the server with the desired URL:

Remember to url encode the target URL before sending the request.

To open https://www.example.com use the following command:
```bash
curl "http://127.0.0.1:42830/?url=https%3A%2F%2Fwww.example.com"
```

This will open `https://www.example.com` in a private Microsoft Edge window.

### Stop the server:

```bash
private-proxy --stop
```
or
```bash
curl "http://127.0.0.1:42310/admin/shutdown"
```

### Set on-start config

```bash
curl "http://127.0.0.1:42310/admin/?on-start=true"
```
or 
```bash
curl "http://127.0.0.1:42310/admin/?on-start=false"
```
or change it in the conf.json file

## API

### `GET /`

Opens the provided URL in a private MS Edge window.

**Parameters:**

- `url` (required) - The URL to open.

### `GET /admin/`

The URL to access admin settings of the server.

**Parameters:**

- `on-start` (optional) - Boolean, sets the on-start variable

**Paths:**

- `shutdown` (optional) - Shuts down the server.

## Limitations

This utility assumes that the `msedge` executable is available in the system's PATH.

## Security Notes

- This server should only be run in a local or trusted environment. Do not expose it to the public internet without adequate security measures.
- Always be cautious about the URLs you open.

## License

[ISC](./LICENSE)
